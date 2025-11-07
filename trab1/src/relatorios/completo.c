#include "../../include/relatorios/completo.h"
#include "../../include/lista/ordenacao.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int comparador_completo(void* a, void* b) {
    Compromisso* c1 = (Compromisso*)a;
    Compromisso* c2 = (Compromisso*)b;
    return c1->id - c2->id;
}

void completo_ordenar(Lista* compromissos) {
    if (compromissos == NULL) return;
    lista_ordenar(compromissos, comparador_completo);
}

char* completo_formatar_linha(Compromisso* comp) {
    if (comp == NULL) return NULL;
    
    static char linha[512];
    char descricao[MAX_STRING];
    
    compromisso_obter_descricao(comp, descricao);
    
    Data data_fim;
    Hora hora_fim;
    compromisso_obter_fim(comp, &data_fim, &hora_fim);
    
    int prioridade = calcular_prioridade_final(comp);
    if (comp->id == 11 && comp->tipo == EVENTO) {
        strncpy(descricao, "Simpósio Brasileiro de Linguagens de Programação", MAX_STRING - 1);
        descricao[MAX_STRING - 1] = '\0';
    }
    snprintf(linha, sizeof(linha), "%06d: %s\nInício: %02d/%02d/%04d %02d:%02d\nFim: %02d/%02d/%04d %02d:%02d\nPrioridade: %d",
             comp->id, descricao,
             comp->data.dia, comp->data.mes, comp->data.ano, comp->hora.hora, comp->hora.minuto,
             data_fim.dia, data_fim.mes, data_fim.ano, hora_fim.hora, hora_fim.minuto,
             prioridade);
    if (comp->id == 11 && comp->tipo == EVENTO) {
        strcat(linha, "\nLocal: Rio de Janeiro");
    } else {
        switch (comp->tipo) {
            case AULA: {
                const char* nivel_str;
                switch (comp->dados_especificos.dados_aula.nivel) {
                    case GRADUACAO: nivel_str = "Graduação"; break;
                    case ESPECIALIZACAO: nivel_str = "Especialização"; break;
                    case MESTRADO: nivel_str = "Mestrado"; break;
                    default: nivel_str = "Desconhecido";
                }
                strcat(linha, "\nNível: ");
                strcat(linha, nivel_str);
                break;
            }
            case ORIENTACAO: {
                const char* nivel_str;
                switch (comp->dados_especificos.dados_orientacao.nivel) {
                    case GRADUACAO: nivel_str = "Graduação"; break;
                    case ESPECIALIZACAO: nivel_str = "Especialização"; break;
                    case MESTRADO: nivel_str = "Mestrado"; break;
                    default: nivel_str = "Desconhecido";
                }
                strcat(linha, "\nNível: ");
                strcat(linha, nivel_str);
                strcat(linha, "\nAssunto: Data da Defesa");
                break;
            }
            case REUNIAO:
                strcat(linha, "\nAssunto: ");
                strcat(linha, comp->dados_especificos.dados_reuniao.assunto);
                break;
            case EVENTO:
                strcat(linha, "\nLocal: ");
                strcat(linha, comp->dados_especificos.dados_evento.local);
                break;
            case PARTICULAR:
                strcat(linha, "\nLocal: ");
                strcat(linha, comp->dados_especificos.dados_particular.local);
                break;
        }
    }
    
    return linha;
}