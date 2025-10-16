#include "../../include/classes/particular.h"
#include <string.h>

Compromisso* particular_criar(int id, Data data, Hora hora, int duracao_minutos,
                             bool adiavel, const char* motivo, const char* local, int grau_prioridade) {
    // Cria compromisso base
    Compromisso* particular = compromisso_criar_base(id, PARTICULAR, data, hora, duracao_minutos, grau_prioridade);
    if (particular == NULL) return NULL;
    
    // Sobrescreve adiável
    particular->adiavel = adiavel;
    
    // Preenche dados específicos
    strncpy(particular->dados_particular.motivo, motivo, MAX_STRING - 1);
    particular->dados_particular.motivo[MAX_STRING - 1] = '\0';
    strncpy(particular->dados_particular.local, local, MAX_STRING - 1);
    particular->dados_particular.local[MAX_STRING - 1] = '\0';
    
    return particular;
}

void particular_imprimir_completo(Compromisso* particular) {
    if (particular == NULL || particular->tipo != PARTICULAR) return;
    
    char descricao[MAX_STRING];
    compromisso_obter_descricao(particular, descricao);
    
    Data data_fim;
    Hora hora_fim;
    compromisso_obter_fim(particular, &data_fim, &hora_fim);
    
    printf("%06d: %s\n", particular->id, descricao);
    printf("Início: ");
    imprimir_data(particular->data);
    printf(" ");
    imprimir_hora(particular->hora);
    printf("\nFim: ");
    imprimir_data(data_fim);
    printf(" ");
    imprimir_hora(hora_fim);
    printf("\nPrioridade: %d\n", compromisso_calcular_prioridade(particular));
    printf("Local: %s\n", particular->dados_particular.local);
}