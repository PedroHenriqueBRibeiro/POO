#include "../../include/relatorios/confirmados.h"
#include "../../include/lista/ordenacao.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Comparador para ordenação de confirmados (data/hora crescente)
int comparador_confirmados(void* a, void* b) {
    Compromisso* c1 = (Compromisso*)a;
    Compromisso* c2 = (Compromisso*)b;
    
    DateTime dt1 = criar_datetime(c1->data, c1->hora);
    DateTime dt2 = criar_datetime(c2->data, c2->hora);
    return comparar_datetime(dt1, dt2);
}

void confirmados_ordenar(Lista* compromissos) {
    if (compromissos == NULL) return;
    lista_ordenar(compromissos, comparador_confirmados);
}

char* confirmados_formatar_linha(Compromisso* comp) {
    if (comp == NULL) return NULL;
    
    static char linha[256];
    char descricao[MAX_STRING];
    
    compromisso_obter_descricao(comp, descricao);
    
    snprintf(linha, sizeof(linha), "%02d/%02d/%04d %02d:%02d\n%06d\n%s\n",
             comp->data.dia, comp->data.mes, comp->data.ano,
             comp->hora.hora, comp->hora.minuto,
             comp->id, descricao);
    
    return linha;
}