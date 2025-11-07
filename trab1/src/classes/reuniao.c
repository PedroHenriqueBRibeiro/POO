#include "../../include/classes/reuniao.h"
#include <string.h>

Compromisso* reuniao_criar(int id, Data data, Hora hora, int duracao_minutos, bool adiavel, const char* assunto, int grau_prioridade) {
    Compromisso* reuniao = compromisso_criar_base(id, REUNIAO, data, hora, duracao_minutos, grau_prioridade);
    if (reuniao == NULL) return NULL;
    reuniao->adiavel = adiavel;
    strncpy(reuniao->dados_especificos.dados_reuniao.assunto, assunto, MAX_STRING - 1);
    reuniao->dados_especificos.dados_reuniao.assunto[MAX_STRING - 1] = '\0';
    
    return reuniao;
}

void reuniao_imprimir_completo(Compromisso* reuniao) {
    if (reuniao == NULL || reuniao->tipo != REUNIAO) return;
    
    char descricao[MAX_STRING];
    compromisso_obter_descricao(reuniao, descricao);
    
    Data data_fim;
    Hora hora_fim;
    compromisso_obter_fim(reuniao, &data_fim, &hora_fim);
    
    printf("%06d: %s\n", reuniao->id, descricao);
    printf("Início: ");
    imprimir_data(reuniao->data);
    printf(" ");
    imprimir_hora(reuniao->hora);
    printf("\nFim: ");
    imprimir_data(data_fim);
    printf(" ");
    imprimir_hora(hora_fim);
    printf("\nPrioridade: %d\n", compromisso_calcular_prioridade(reuniao));
    printf("Assunto: %s\n", reuniao->dados_especificos.dados_reuniao.assunto);
}