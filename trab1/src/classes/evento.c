#include "../../include/classes/evento.h"
#include <string.h>

Compromisso* evento_criar(int id, Data data, Hora hora, int duracao_dias,
                         const char* nome_evento, const char* local, int grau_prioridade) {
    // Converte duração de dias para minutos (simplificado)
    int duracao_minutos = duracao_dias * 24 * 60;
    
    // Cria compromisso base
    Compromisso* evento = compromisso_criar_base(id, EVENTO, data, hora, duracao_minutos, grau_prioridade);
    if (evento == NULL) return NULL;
    
    // Preenche dados específicos
    strncpy(evento->dados_evento.nome_evento, nome_evento, MAX_STRING - 1);
    evento->dados_evento.nome_evento[MAX_STRING - 1] = '\0';
    strncpy(evento->dados_evento.local, local, MAX_STRING - 1);
    evento->dados_evento.local[MAX_STRING - 1] = '\0';
    evento->dados_evento.duracao_dias = duracao_dias;
    
    return evento;
}

void evento_imprimir_completo(Compromisso* evento) {
    if (evento == NULL || evento->tipo != EVENTO) return;
    
    char descricao[MAX_STRING];
    compromisso_obter_descricao(evento, descricao);
    
    Data data_fim;
    Hora hora_fim;
    compromisso_obter_fim(evento, &data_fim, &hora_fim);
    
    printf("%06d: %s\n", evento->id, descricao);
    printf("Início: ");
    imprimir_data(evento->data);
    printf(" ");
    imprimir_hora(evento->hora);
    printf("\nFim: ");
    imprimir_data(data_fim);
    printf(" ");
    imprimir_hora(hora_fim);
    printf("\nPrioridade: %d\n", compromisso_calcular_prioridade(evento));
    printf("Local: %s\n", evento->dados_evento.local);
}