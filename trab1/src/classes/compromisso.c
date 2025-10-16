#include "../../include/classes/compromisso.h"
#include <string.h>

// Função virtual para calcular prioridade
int compromisso_calcular_prioridade(Compromisso* comp) {
    if (comp == NULL) return 0;
    
    int fator = comp->fator_multiplicador;
    
    // Se for inadiável (e não for aula ou evento que já são inadiáveis por natureza)
    if (!comp->adiavel && comp->tipo != AULA && comp->tipo != EVENTO) {
        fator += 1;
    }
    
    return comp->grau_prioridade * fator;
}

// Função virtual para obter descrição
void compromisso_obter_descricao(Compromisso* comp, char* buffer) {
    if (comp == NULL || buffer == NULL) return;
    
    switch (comp->tipo) {
        case AULA:
            snprintf(buffer, MAX_STRING, "Aula de %s", comp->dados_aula.nome_disciplina);
            break;
        case ORIENTACAO:
            snprintf(buffer, MAX_STRING, "Orientação de %s", comp->dados_orientacao.nome_orientado);
            break;
        case REUNIAO:
            strcpy(buffer, "Reunião de Departamento");
            break;
        case EVENTO:
            snprintf(buffer, MAX_STRING, "%s", comp->dados_evento.nome_evento);
            break;
        case PARTICULAR:
            snprintf(buffer, MAX_STRING, "%s", comp->dados_particular.motivo);
            break;
        default:
            strcpy(buffer, "Compromisso desconhecido");
    }
}

// Função virtual para obter data/hora fim
void compromisso_obter_fim(Compromisso* comp, Data* data_fim, Hora* hora_fim) {
    if (comp == NULL) return;
    
    *data_fim = comp->data;
    *hora_fim = comp->hora;
    
    // Adiciona duração em minutos
    int minutos_totais = hora_fim->minuto + comp->duracao_minutos;
    hora_fim->hora += minutos_totais / 60;
    hora_fim->minuto = minutos_totais % 60;
    
    // Ajusta dia se passar de 24h (simplificado)
    if (hora_fim->hora >= 24) {
        hora_fim->hora -= 24;
        data_fim->dia++;
        // Aqui precisaria de lógica mais complexa para meses/anos
    }
}

// Construtor base
Compromisso* compromisso_criar_base(int id, TipoCompromisso tipo, Data data, Hora hora, 
                                   int duracao_minutos, int grau_prioridade) {
    Compromisso* comp = (Compromisso*)malloc(sizeof(Compromisso));
    if (comp == NULL) return NULL;
    
    comp->id = id;
    comp->tipo = tipo;
    comp->data = data;
    comp->hora = hora;
    comp->duracao_minutos = duracao_minutos;
    comp->grau_prioridade = grau_prioridade;
    
    // Define fator multiplicador base conforme tabela
    switch (tipo) {
        case AULA: comp->fator_multiplicador = 2; break;
        case ORIENTACAO: comp->fator_multiplicador = 1; break;
        case REUNIAO: comp->fator_multiplicador = 4; break;
        case EVENTO: comp->fator_multiplicador = 3; break;
        case PARTICULAR: comp->fator_multiplicador = 2; break;
        default: comp->fator_multiplicador = 1;
    }
    
    // Define se é adiável (aulas e eventos nunca são adiáveis)
    comp->adiavel = (tipo != AULA && tipo != EVENTO);
    
    return comp;
}

// Destruidor
void compromisso_destruir(Compromisso* comp) {
    if (comp != NULL) {
        free(comp);
    }
}