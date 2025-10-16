#include "../../include/io/leitor.h"
#include "../../include/classes/aula.h"
#include "../../include/classes/orientacao.h"
#include "../../include/classes/reuniao.h"
#include "../../include/classes/evento.h"
#include "../../include/classes/particular.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

Lista* ler_agenda(const char* nome_arquivo) {
    FILE* arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) return NULL;
    
    Lista* compromissos = lista_criar();
    if (compromissos == NULL) {
        fclose(arquivo);
        return NULL;
    }
    
    char linha[MAX_LINE];
    
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        trim_string(linha);
        
        // Linha em branco - pula
        if (strlen(linha) == 0) continue;
        
        // Processa compromisso
        Compromisso* comp = parse_compromisso(linha, arquivo);
        if (comp != NULL) {
            lista_inserir_fim(compromissos, comp);
        }
        
        // Pula linha em branco entre compromissos
        fgets(linha, sizeof(linha), arquivo); // linha em branco
    }
    
    fclose(arquivo);
    return compromissos;
}

PosicoesRelatorio ler_posicoes(const char* nome_arquivo) {
    PosicoesRelatorio pos = {0, 0, 0, 0};
    FILE* arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) return pos;
    
    char linha[MAX_LINE];
    
    if (fgets(linha, sizeof(linha), arquivo)) pos.i = atoi(linha);
    if (fgets(linha, sizeof(linha), arquivo)) pos.j = atoi(linha);
    if (fgets(linha, sizeof(linha), arquivo)) pos.k = atoi(linha);
    if (fgets(linha, sizeof(linha), arquivo)) pos.m = atoi(linha);
    
    fclose(arquivo);
    return pos;
}

// ... código anterior ...

Compromisso* parse_compromisso(const char* linha_tipo, FILE* arquivo) {
    if (linha_tipo == NULL || strlen(linha_tipo) < 2) return NULL;
    
    char tipo = linha_tipo[0];
    int id = atoi(linha_tipo + 1);
    
    char linha[MAX_LINE];
    char data_str[11], hora_str[6];
    
    // Lê data e hora
    fgets(linha, sizeof(linha), arquivo);
    sscanf(linha, "%10s %5s", data_str, hora_str);
    
    Data data = ler_data(data_str);
    Hora hora = ler_hora(hora_str);
    
    // Lê duração
    fgets(linha, sizeof(linha), arquivo);
    int duracao = atoi(linha);
    
    switch (tipo) {
        case 'A': { // Aula
            char disciplina[MAX_STRING];
            char nivel_str[MAX_STRING];
            int prioridade;
            
            fgets(disciplina, sizeof(disciplina), arquivo);
            trim_string(disciplina);
            
            fgets(nivel_str, sizeof(nivel_str), arquivo);
            trim_string(nivel_str);
            
            fgets(linha, sizeof(linha), arquivo);
            prioridade = atoi(linha);
            
            Nivel nivel;
            if (strcmp(nivel_str, "Graduação") == 0) nivel = GRADUACAO;
            else if (strcmp(nivel_str, "Especialização") == 0) nivel = ESPECIALIZACAO;
            else if (strcmp(nivel_str, "Mestrado") == 0) nivel = MESTRADO;
            else nivel = GRADUACAO;
            
            return aula_criar(id, data, hora, duracao, disciplina, nivel, prioridade);
        }
        
        case 'O': { // Orientação
            char adiavel_str[10];
            char nome_orientado[MAX_STRING];
            char nivel_str[MAX_STRING];
            char data_defesa_str[11], hora_defesa_str[6];
            int prioridade;
            
            fgets(adiavel_str, sizeof(adiavel_str), arquivo);
            trim_string(adiavel_str);
            bool adiavel = string_para_bool(adiavel_str);
            
            fgets(nome_orientado, sizeof(nome_orientado), arquivo);
            trim_string(nome_orientado);
            
            fgets(nivel_str, sizeof(nivel_str), arquivo);
            trim_string(nivel_str);
            
            fgets(linha, sizeof(linha), arquivo);
            sscanf(linha, "%10s %5s", data_defesa_str, hora_defesa_str);
            
            fgets(linha, sizeof(linha), arquivo);
            prioridade = atoi(linha);
            
            Nivel nivel;
            if (strcmp(nivel_str, "Graduação") == 0) nivel = GRADUACAO;
            else if (strcmp(nivel_str, "Especialização") == 0) nivel = ESPECIALIZACAO;
            else if (strcmp(nivel_str, "Mestrado") == 0) nivel = MESTRADO;
            else nivel = GRADUACAO;
            
            Data data_defesa = ler_data(data_defesa_str);
            Hora hora_defesa = ler_hora(hora_defesa_str);
            
            return orientacao_criar(id, data, hora, duracao, adiavel, nome_orientado, 
                                   nivel, data_defesa, hora_defesa, prioridade);
        }
        
        case 'R': { // Reunião
            char adiavel_str[10];
            char assunto[MAX_STRING];
            int prioridade;
            
            fgets(adiavel_str, sizeof(adiavel_str), arquivo);
            trim_string(adiavel_str);
            bool adiavel = string_para_bool(adiavel_str);
            
            fgets(assunto, sizeof(assunto), arquivo);
            trim_string(assunto);
            
            fgets(linha, sizeof(linha), arquivo);
            prioridade = atoi(linha);
            
            return reuniao_criar(id, data, hora, duracao, adiavel, assunto, prioridade);
        }
        
        case 'E': { // Evento
            char nome_evento[MAX_STRING];
            char local[MAX_STRING];
            int prioridade;
            
            fgets(nome_evento, sizeof(nome_evento), arquivo);
            trim_string(nome_evento);
            
            fgets(local, sizeof(local), arquivo);
            trim_string(local);
            
            fgets(linha, sizeof(linha), arquivo);
            prioridade = atoi(linha);
            
            return evento_criar(id, data, hora, duracao, nome_evento, local, prioridade);
        }
        
        case 'P': { // Particular
            char adiavel_str[10];
            char motivo[MAX_STRING];
            char local[MAX_STRING];
            int prioridade;
            
            fgets(adiavel_str, sizeof(adiavel_str), arquivo);
            trim_string(adiavel_str);
            bool adiavel = string_para_bool(adiavel_str);
            
            fgets(motivo, sizeof(motivo), arquivo);
            trim_string(motivo);
            
            fgets(local, sizeof(local), arquivo);
            trim_string(local);
            
            fgets(linha, sizeof(linha), arquivo);
            prioridade = atoi(linha);
            
            return particular_criar(id, data, hora, duracao, adiavel, motivo, local, prioridade);
        }
        
        default:
            return NULL;
    }
}