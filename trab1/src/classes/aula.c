#include "../../include/classes/aula.h"
#include <string.h>

Compromisso* aula_criar(int id, Data data, Hora hora, int duracao_minutos, const char* nome_disciplina, Nivel nivel, int grau_prioridade) {
    Compromisso* aula = compromisso_criar_base(id, AULA, data, hora, duracao_minutos, grau_prioridade);
    if (aula == NULL) return NULL;
    strncpy(aula->dados_especificos.dados_aula.nome_disciplina, nome_disciplina, MAX_STRING - 1);
    aula->dados_especificos.dados_aula.nome_disciplina[MAX_STRING - 1] = '\0';
    aula->dados_especificos.dados_aula.nivel = nivel;
    
    return aula;
}
void aula_imprimir_completo(Compromisso* aula) {
    if (aula == NULL || aula->tipo != AULA) return;
    char descricao[MAX_STRING];
    compromisso_obter_descricao(aula, descricao);    
    Data data_fim;
    Hora hora_fim;
    compromisso_obter_fim(aula, &data_fim, &hora_fim);
    
    printf("%06d: %s\n", aula->id, descricao);
    printf("Início: ");
    imprimir_data(aula->data);
    printf(" ");
    imprimir_hora(aula->hora);
    printf("\nFim: ");
    imprimir_data(data_fim);
    printf(" ");
    imprimir_hora(hora_fim);
    printf("\nPrioridade: %d\n", compromisso_calcular_prioridade(aula));
    
    const char* nivel_str;
    switch (aula->dados_especificos.dados_aula.nivel) {
        case GRADUACAO: nivel_str = "Graduação"; break;
        case ESPECIALIZACAO: nivel_str = "Especialização"; break;
        case MESTRADO: nivel_str = "Mestrado"; break;
        default: nivel_str = "Desconhecido";
    }
    printf("Nível: %s\n", nivel_str);
}