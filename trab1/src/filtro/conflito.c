#include "../../include/filtro/conflito.h"
#include "../../include/lista/no.h"
#include <stdlib.h>

bool compromissos_conflitam(Compromisso* c1, Compromisso* c2) {
    if (c1 == NULL || c2 == NULL) return false;
    if (c1->id == c2->id) return false;
    if ((c1->id == 11 && c2->id == 3) || (c1->id == 3 && c2->id == 11)) {
        printf("=== DEBUG CONFLITO 000011 vs 000003 ===\n");
    }
    if (c1->tipo == EVENTO || c2->tipo == EVENTO) {
        Compromisso* evento = (c1->tipo == EVENTO) ? c1 : c2;
        Compromisso* outro = (c1->tipo == EVENTO) ? c2 : c1;
        
        Data data_fim_evento = evento->data;
        data_fim_evento.dia += evento->dados_especificos.dados_evento.duracao_dias;
        if (comparar_datas(outro->data, evento->data) >= 0 && 
            comparar_datas(outro->data, data_fim_evento) <= 0) {
            
            if ((c1->id == 11 && c2->id == 3) || (c1->id == 3 && c2->id == 11)) {
                printf("Evento 000011: %02d/%02d/%04d a %02d/%02d/%04d\n",
                       evento->data.dia, evento->data.mes, evento->data.ano,
                       data_fim_evento.dia, data_fim_evento.mes, data_fim_evento.ano);
                printf("Aula 000003: %02d/%02d/%04d\n",
                       outro->data.dia, outro->data.mes, outro->data.ano);
                printf("CONFLITO DETECTADO!\n");
            }
            return true;
        }
    }
    if (comparar_datas(c1->data, c2->data) != 0) return false;
    Data data_fim1, data_fim2;
    Hora hora_fim1, hora_fim2;
    compromisso_obter_fim(c1, &data_fim1, &hora_fim1);
    compromisso_obter_fim(c2, &data_fim2, &hora_fim2);
    
    DateTime inicio1 = criar_datetime(c1->data, c1->hora);
    DateTime fim1 = criar_datetime(data_fim1, hora_fim1);
    DateTime inicio2 = criar_datetime(c2->data, c2->hora);
    DateTime fim2 = criar_datetime(data_fim2, hora_fim2);
    
    return (comparar_datetime(inicio1, fim2) < 0 && comparar_datetime(fim1, inicio2) > 0) ||
           (comparar_datetime(inicio2, fim1) < 0 && comparar_datetime(fim2, inicio1) > 0);
}
Lista* detectar_todos_conflitos(Lista* compromissos) {
    if (compromissos == NULL) return NULL;
    
    Lista* conflitos = lista_criar();
    if (conflitos == NULL) return NULL;
    No* atual_i = compromissos->inicio;
    while (atual_i != NULL) {
        Compromisso* comp_i = (Compromisso*)atual_i->dado;
        No* atual_j = atual_i->proximo;
        
        while (atual_j != NULL) {
            Compromisso* comp_j = (Compromisso*)atual_j->dado;
            
            if (compromissos_conflitam(comp_i, comp_j)) {
                Conflito* conflito = (Conflito*)malloc(sizeof(Conflito));
                if (conflito != NULL) {
                    conflito->comp1 = comp_i;
                    conflito->comp2 = comp_j;
                    conflito->prioridade_comp1 = calcular_prioridade_final(comp_i);
                    conflito->prioridade_comp2 = calcular_prioridade_final(comp_j);
                    lista_inserir_fim(conflitos, conflito);
                }
            }
            atual_j = atual_j->proximo;
        }
        atual_i = atual_i->proximo;
    }
    
    return conflitos;
}