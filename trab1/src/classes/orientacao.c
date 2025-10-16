#include "../../include/classes/orientacao.h"
#include <string.h>

Compromisso* orientacao_criar(int id, Data data, Hora hora, int duracao_minutos,
                             bool adiavel, const char* nome_orientado, Nivel nivel,
                             Data data_defesa, Hora hora_defesa, int grau_prioridade) {
    // Cria compromisso base
    Compromisso* orientacao = compromisso_criar_base(id, ORIENTACAO, data, hora, duracao_minutos, grau_prioridade);
    if (orientacao == NULL) return NULL;
    
    // Sobrescreve adiável (pois orientação pode ser adiável)
    orientacao->adiavel = adiavel;
    
    // Preenche dados específicos
    strncpy(orientacao->dados_orientacao.nome_orientado, nome_orientado, MAX_STRING - 1);
    orientacao->dados_orientacao.nome_orientado[MAX_STRING - 1] = '\0';
    orientacao->dados_orientacao.nivel = nivel;
    orientacao->dados_orientacao.data_defesa = data_defesa;
    orientacao->dados_orientacao.hora_defesa = hora_defesa;
    
    return orientacao;
}

void orientacao_imprimir_completo(Compromisso* orientacao) {
    if (orientacao == NULL || orientacao->tipo != ORIENTACAO) return;
    
    char descricao[MAX_STRING];
    compromisso_obter_descricao(orientacao, descricao);
    
    Data data_fim;
    Hora hora_fim;
    compromisso_obter_fim(orientacao, &data_fim, &hora_fim);
    
    printf("%06d: %s\n", orientacao->id, descricao);
    printf("Início: ");
    imprimir_data(orientacao->data);
    printf(" ");
    imprimir_hora(orientacao->hora);
    printf("\nFim: ");
    imprimir_data(data_fim);
    printf(" ");
    imprimir_hora(hora_fim);
    printf("\nPrioridade: %d\n", compromisso_calcular_prioridade(orientacao));
    
    const char* nivel_str;
    switch (orientacao->dados_orientacao.nivel) {
        case GRADUACAO: nivel_str = "Graduação"; break;
        case ESPECIALIZACAO: nivel_str = "Especialização"; break;
        case MESTRADO: nivel_str = "Mestrado"; break;
        default: nivel_str = "Desconhecido";
    }
    printf("Nível: %s\n", nivel_str);
    printf("Data da Defesa: ");
    imprimir_data(orientacao->dados_orientacao.data_defesa);
    printf(" ");
    imprimir_hora(orientacao->dados_orientacao.hora_defesa);
    printf("\n");
}