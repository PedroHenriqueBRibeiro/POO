#include "../../include/relatorios/cancelados.h"
#include "../../include/lista/ordenacao.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Comparador para ordenação de cancelados (duração crescente)
int comparador_cancelados(void* a, void* b) {
    CompromissoCancelado* cc1 = (CompromissoCancelado*)a;
    CompromissoCancelado* cc2 = (CompromissoCancelado*)b;
    
    return cc1->compromisso->duracao_minutos - cc2->compromisso->duracao_minutos;
}

void cancelados_ordenar(Lista* compromissos_cancelados) {
    if (compromissos_cancelados == NULL) return;
    lista_ordenar(compromissos_cancelados, comparador_cancelados);
}

char* cancelados_formatar_linha(CompromissoCancelado* comp_cancelado) {
    if (comp_cancelado == NULL || comp_cancelado->compromisso == NULL) return NULL;
    
    static char linha[256];
    char descricao[MAX_STRING];
    
    compromisso_obter_descricao(comp_cancelado->compromisso, descricao);
    int prioridade = calcular_prioridade_final(comp_cancelado->compromisso);
    
    snprintf(linha, sizeof(linha), "%06d\n%s\n%d\n%06d\n",
             comp_cancelado->compromisso->id, descricao, prioridade,
             comp_cancelado->conflitante ? comp_cancelado->conflitante->id : 0);
    
    return linha;
}