#include "../../include/filtro/prioridade.h"
#include <string.h>

int calcular_prioridade_final(Compromisso* comp) {
    return compromisso_calcular_prioridade(comp);
}

int comparar_prioridades(Compromisso* c1, Compromisso* c2) {
    int p1 = calcular_prioridade_final(c1);
    int p2 = calcular_prioridade_final(c2);
    return p1 - p2;
}

int comparar_prioridades_com_desempate(Compromisso* c1, Compromisso* c2) {
    int cmp_prioridade = comparar_prioridades(c1, c2);
    if (cmp_prioridade != 0) return cmp_prioridade;
    
    // Desempate 1: que inicia primeiro
    DateTime dt1 = criar_datetime(c1->data, c1->hora);
    DateTime dt2 = criar_datetime(c2->data, c2->hora);
    int cmp_datetime = comparar_datetime(dt1, dt2);
    if (cmp_datetime != 0) return cmp_datetime;
    
    // Desempate 2: tipo de compromisso
    if (c1->tipo != c2->tipo) {
        // Ordem: reunião(4), evento(3), aula(2), particular(2), orientação(1)
        int prioridade_tipo1 = (c1->tipo == REUNIAO) ? 5 : 
                              (c1->tipo == EVENTO) ? 4 :
                              (c1->tipo == AULA) ? 3 :
                              (c1->tipo == PARTICULAR) ? 2 : 1;
                              
        int prioridade_tipo2 = (c2->tipo == REUNIAO) ? 5 : 
                              (c2->tipo == EVENTO) ? 4 :
                              (c2->tipo == AULA) ? 3 :
                              (c2->tipo == PARTICULAR) ? 2 : 1;
        
        if (prioridade_tipo1 != prioridade_tipo2) {
            return prioridade_tipo2 - prioridade_tipo1; // Maior prioridade primeiro
        }
    }
    
    // Desempate 3: ordem alfabética da descrição
    char desc1[MAX_STRING], desc2[MAX_STRING];
    compromisso_obter_descricao(c1, desc1);
    compromisso_obter_descricao(c2, desc2);
    return strcmp(desc1, desc2);
}

const char* obter_nome_tipo_prioridade(TipoCompromisso tipo) {
    switch (tipo) {
        case AULA: return "Aula";
        case ORIENTACAO: return "Orientação";
        case REUNIAO: return "Reunião";
        case EVENTO: return "Evento";
        case PARTICULAR: return "Particular";
        default: return "Desconhecido";
    }
}