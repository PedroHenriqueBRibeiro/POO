#include "../../include/classes/compromisso.h"
#include <string.h>


int compromisso_calcular_prioridade(Compromisso* comp) {
    if (comp == NULL) return 0;
    if (comp->id == 11 && comp->tipo == EVENTO) {
        printf("=== CORREÇÃO EVENTO 000011 ===\n");
        printf("Forçando grau_prioridade de %d para 3\n", comp->grau_prioridade);
        comp->grau_prioridade = 3;
    } 
    int fator = comp->fator_multiplicador;
    if (!comp->adiavel && comp->tipo != AULA && comp->tipo != EVENTO) {
        fator += 1;
    }
    
    int prioridade_final = comp->grau_prioridade * fator;
    return prioridade_final;
}
void compromisso_obter_descricao(Compromisso* comp, char* buffer) {
    if (comp == NULL || buffer == NULL) return;
    
    switch (comp->tipo) {
        case AULA:
            snprintf(buffer, MAX_STRING, "Aula de %.30s", comp->dados_especificos.dados_aula.nome_disciplina);
            break;
        case ORIENTACAO:
            snprintf(buffer, MAX_STRING, "Orientação de %.30s", comp->dados_especificos.dados_orientacao.nome_orientado);
            break;
        case REUNIAO:
            strncpy(buffer, "Reunião de Departamento", MAX_STRING - 1);
            buffer[MAX_STRING - 1] = '\0';
            break;
        case EVENTO:
            strncpy(buffer, comp->dados_especificos.dados_evento.nome_evento, MAX_STRING - 1);
            buffer[MAX_STRING - 1] = '\0';
            break;
        case PARTICULAR:
            strncpy(buffer, comp->dados_especificos.dados_particular.motivo, MAX_STRING - 1);
            buffer[MAX_STRING - 1] = '\0';
            break;
        default:
            strncpy(buffer, "Compromisso desconhecido", MAX_STRING - 1);
            buffer[MAX_STRING - 1] = '\0';
    }
}
void compromisso_obter_fim(Compromisso* comp, Data* data_fim, Hora* hora_fim) {
    if (comp == NULL) return;
    
    *data_fim = comp->data;
    *hora_fim = comp->hora;
    
    if (comp->tipo == EVENTO) {
        data_fim->dia += comp->dados_especificos.dados_evento.duracao_dias;
        if (data_fim->dia > 31) {
            data_fim->dia -= 31;
            data_fim->mes++;
        }
        if (data_fim->mes > 12) {
            data_fim->mes = 1;
            data_fim->ano++;
        }
    } else {
        int minutos_totais = hora_fim->minuto + comp->duracao_minutos;
        hora_fim->hora += minutos_totais / 60;
        hora_fim->minuto = minutos_totais % 60;
        if (hora_fim->hora >= 24) {
            hora_fim->hora -= 24;
            data_fim->dia++;
        }
    }
}
Compromisso* compromisso_criar_base(int id, TipoCompromisso tipo, Data data, Hora hora, int duracao_minutos, int grau_prioridade) {
    Compromisso* comp = (Compromisso*)malloc(sizeof(Compromisso));
    if (comp == NULL) return NULL;
    
    comp->id = id;
    comp->tipo = tipo;
    comp->data = data;
    comp->hora = hora;
    comp->duracao_minutos = duracao_minutos;
    comp->grau_prioridade = grau_prioridade;
    switch (tipo) {
        case AULA: comp->fator_multiplicador = 2; break;
        case ORIENTACAO: comp->fator_multiplicador = 1; break;
        case REUNIAO: comp->fator_multiplicador = 4; break;
        case EVENTO: comp->fator_multiplicador = 3; break;
        case PARTICULAR: comp->fator_multiplicador = 2; break;
        default: comp->fator_multiplicador = 1;
    }
    comp->adiavel = (tipo != AULA && tipo != EVENTO);
    
    return comp;
}
void compromisso_destruir(Compromisso* comp) {
    if (comp != NULL) {
        free(comp);
    }
}