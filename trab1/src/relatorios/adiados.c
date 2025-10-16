#include "../../include/relatorios/adiados.h"
#include "../../include/lista/ordenacao.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Comparador para ordenação de adiados (prioridade decrescente)
int comparador_adiados(void* a, void* b) {
    CompromissoAdiado* ca1 = (CompromissoAdiado*)a;
    CompromissoAdiado* ca2 = (CompromissoAdiado*)b;
    
    int p1 = calcular_prioridade_final(ca1->compromisso);
    int p2 = calcular_prioridade_final(ca2->compromisso);
    
    // Ordem decrescente
    return p2 - p1;
}

void adiados_ordenar(Lista* compromissos_adiados) {
    if (compromissos_adiados == NULL) return;
    lista_ordenar(compromissos_adiados, comparador_adiados);
}

char* adiados_formatar_linha(CompromissoAdiado* comp_adiado) {
    if (comp_adiado == NULL || comp_adiado->compromisso == NULL) return NULL;
    
    static char linha[256];
    char descricao[MAX_STRING];
    
    compromisso_obter_descricao(comp_adiado->compromisso, descricao);
    int prioridade = calcular_prioridade_final(comp_adiado->compromisso);
    
    snprintf(linha, sizeof(linha), "%06d\n%s\n%d\n%06d\n",
             comp_adiado->compromisso->id, descricao, prioridade,
             comp_adiado->conflitante ? comp_adiado->conflitante->id : 0);
    
    return linha;
}