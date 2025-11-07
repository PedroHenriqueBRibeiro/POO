#ifndef COMPROMISSO_H
#define COMPROMISSO_H

#include "../common.h"
#include "../data/data.h"
#include "../data/hora.h"
typedef union {
    struct {
        char nome_disciplina[MAX_STRING];
        Nivel nivel;
    } dados_aula;
    
    struct {
        char nome_orientado[MAX_STRING];
        Nivel nivel;
        Data data_defesa;
        Hora hora_defesa;
    } dados_orientacao;
    
    struct {
        char assunto[MAX_STRING];
    } dados_reuniao;
    
    struct {
        char nome_evento[MAX_STRING];
        char local[MAX_STRING];
        int duracao_dias;
    } dados_evento;
    
    struct {
        char motivo[MAX_STRING];
        char local[MAX_STRING];
    } dados_particular;
} DadosCompromisso;
typedef struct Compromisso {
    int id;
    TipoCompromisso tipo;
    Data data;
    Hora hora;
    int duracao_minutos;
    int grau_prioridade;
    int fator_multiplicador;
    bool adiavel;
    
    DadosCompromisso dados_especificos;
} Compromisso;
Compromisso* compromisso_criar_base(int id, TipoCompromisso tipo, Data data, Hora hora, 
                                   int duracao_minutos, int grau_prioridade);
int compromisso_calcular_prioridade(Compromisso* comp);
void compromisso_obter_descricao(Compromisso* comp, char* buffer);
void compromisso_obter_fim(Compromisso* comp, Data* data_fim, Hora* hora_fim);
void compromisso_destruir(Compromisso* comp);

#endif