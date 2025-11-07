#include "../../include/io/leitor.h"
#include "../../include/classes/aula.h"
#include "../../include/classes/orientacao.h"
#include "../../include/classes/reuniao.h"
#include "../../include/classes/evento.h"
#include "../../include/classes/particular.h"
#include "../../include/lista/no.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

Lista* ler_agenda(const char* nome_arquivo) {
    FILE* arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        printf("Erro: Não foi possível abrir %s\n", nome_arquivo);
        return NULL;
    }
    Lista* compromissos = lista_criar();
    if (compromissos == NULL) {
        fclose(arquivo);
        return NULL;
    }
    char linha[MAX_LINE];
    int linha_num = 0;
    
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        linha_num++;
        trim_string(linha);
        if (strlen(linha) == 0) continue;
        if (strlen(linha) >= 2 && 
            (linha[0] == 'A' || linha[0] == 'O' || linha[0] == 'R' || linha[0] == 'E' || linha[0] == 'P') &&
            isdigit(linha[1])) {
            Compromisso* comp = parse_compromisso(linha, arquivo, &linha_num);
            if (comp != NULL) {
                lista_inserir_fim(compromissos, comp);
                printf("✓ Compromisso %06d carregado: tipo=%c\n", comp->id, linha[0]);
            } else {
                printf("✗ Erro ao parsear compromisso: %s\n", linha);
            }
        } else {
            printf("? Linha ignorada: %s\n", linha);
        }
    }
    
    fclose(arquivo);
    printf("Total de compromissos carregados: %d\n", lista_tamanho(compromissos));
    return compromissos;
}

PosicoesRelatorio ler_posicoes(const char* nome_arquivo) {
    PosicoesRelatorio pos = {0, 0, 0, 0};
    FILE* arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        printf("Erro: Não foi possível abrir %s\n", nome_arquivo);
        return pos;
    }
    
    char linha[MAX_LINE];
    
    if (fgets(linha, sizeof(linha), arquivo)) {
        trim_string(linha);
        pos.i = atoi(linha);
    }
    if (fgets(linha, sizeof(linha), arquivo)) {
        trim_string(linha);
        pos.j = atoi(linha);
    }
    if (fgets(linha, sizeof(linha), arquivo)) {
        trim_string(linha);
        pos.k = atoi(linha);
    }
    if (fgets(linha, sizeof(linha), arquivo)) {
        trim_string(linha);
        pos.m = atoi(linha);
    }
    
    fclose(arquivo);
    printf("Posições lidas: i=%d, j=%d, k=%d, m=%d\n", pos.i, pos.j, pos.k, pos.m);
    return pos;
}

Compromisso* parse_compromisso(const char* linha_tipo, FILE* arquivo, int* linha_num) {
    if (linha_tipo == NULL || strlen(linha_tipo) < 2) return NULL; 
    char tipo = linha_tipo[0];
    int id = atoi(linha_tipo + 1); 
    printf("  Processando: %c%06d (linha %d)\n", tipo, id, *linha_num);
    char linha[MAX_LINE];
    char data_str[11], hora_str[6];
    if (fgets(linha, sizeof(linha), arquivo) == NULL) return NULL;
    (*linha_num)++;
    trim_string(linha);
    sscanf(linha, "%10s %5s", data_str, hora_str);
    
    Data data = ler_data(data_str);
    Hora hora = ler_hora(hora_str);
    if (fgets(linha, sizeof(linha), arquivo) == NULL) return NULL;
    (*linha_num)++;
    trim_string(linha);
    int duracao = atoi(linha);
    
    switch (tipo) {
        case 'A': {
            char disciplina[MAX_STRING];
            char nivel_str[MAX_STRING];
            int prioridade;
            
            if (fgets(disciplina, sizeof(disciplina), arquivo) == NULL) return NULL;
            (*linha_num)++;
            trim_string(disciplina);
            
            if (fgets(nivel_str, sizeof(nivel_str), arquivo) == NULL) return NULL;
            (*linha_num)++;
            trim_string(nivel_str);
            
            if (fgets(linha, sizeof(linha), arquivo) == NULL) return NULL;
            (*linha_num)++;
            trim_string(linha);
            prioridade = atoi(linha);
            
            Nivel nivel;
            if (strcmp(nivel_str, "Graduação") == 0) nivel = GRADUACAO;
            else if (strcmp(nivel_str, "Especialização") == 0) nivel = ESPECIALIZACAO;
            else if (strcmp(nivel_str, "Mestrado") == 0) nivel = MESTRADO;
            else nivel = GRADUACAO;
            
            printf("    Aula: %s, Nivel: %s, Prioridade: %d\n", disciplina, nivel_str, prioridade);
            return aula_criar(id, data, hora, duracao, disciplina, nivel, prioridade);
        }
        
        case 'O': {
            char adiavel_str[10];
            char nome_orientado[MAX_STRING];
            char nivel_str[MAX_STRING];
            char data_defesa_str[11], hora_defesa_str[6];
            int prioridade;
            
            if (fgets(adiavel_str, sizeof(adiavel_str), arquivo) == NULL) return NULL;
            (*linha_num)++;
            trim_string(adiavel_str);
            bool adiavel = string_para_bool(adiavel_str);
            
            if (fgets(nome_orientado, sizeof(nome_orientado), arquivo) == NULL) return NULL;
            (*linha_num)++;
            trim_string(nome_orientado);
            
            if (fgets(nivel_str, sizeof(nivel_str), arquivo) == NULL) return NULL;
            (*linha_num)++;
            trim_string(nivel_str);
            
            if (fgets(linha, sizeof(linha), arquivo) == NULL) return NULL;
            (*linha_num)++;
            trim_string(linha);
            sscanf(linha, "%10s %5s", data_defesa_str, hora_defesa_str);
            
            if (fgets(linha, sizeof(linha), arquivo) == NULL) return NULL;
            (*linha_num)++;
            trim_string(linha);
            prioridade = atoi(linha);
            
            Nivel nivel;
            if (strcmp(nivel_str, "Graduação") == 0) nivel = GRADUACAO;
            else if (strcmp(nivel_str, "Especialização") == 0) nivel = ESPECIALIZACAO;
            else if (strcmp(nivel_str, "Mestrado") == 0) nivel = MESTRADO;
            else nivel = GRADUACAO;
            
            Data data_defesa = ler_data(data_defesa_str);
            Hora hora_defesa = ler_hora(hora_defesa_str);
            
            printf("    Orientação: %s, Nivel: %s, Adiavel: %d, Prioridade: %d\n", 
                   nome_orientado, nivel_str, adiavel, prioridade);
            return orientacao_criar(id, data, hora, duracao, adiavel, nome_orientado, 
                                   nivel, data_defesa, hora_defesa, prioridade);
        }
        
        case 'R': {
            char adiavel_str[10];
            char assunto[MAX_STRING];
            int prioridade;
            
            if (fgets(adiavel_str, sizeof(adiavel_str), arquivo) == NULL) return NULL;
            (*linha_num)++;
            trim_string(adiavel_str);
            bool adiavel = string_para_bool(adiavel_str);
            
            if (fgets(assunto, sizeof(assunto), arquivo) == NULL) return NULL;
            (*linha_num)++;
            trim_string(assunto);
            
            if (fgets(linha, sizeof(linha), arquivo) == NULL) return NULL;
            (*linha_num)++;
            trim_string(linha);
            prioridade = atoi(linha);
            
            printf("    Reunião: %s, Adiavel: %d, Prioridade: %d\n", assunto, adiavel, prioridade);
            return reuniao_criar(id, data, hora, duracao, adiavel, assunto, prioridade);
        }
        
        case 'E': {
            char nome_evento[MAX_STRING];
            char local[MAX_STRING];
            int prioridade;
            
            if (fgets(nome_evento, sizeof(nome_evento), arquivo) == NULL) return NULL;
            (*linha_num)++;
            trim_string(nome_evento);
            if (id == 11) {
                printf("    DEBUG Evento 000011 - Nome: '%s'\n", nome_evento);
            }
            
            if (fgets(local, sizeof(local), arquivo) == NULL) return NULL;
            (*linha_num)++;
            trim_string(local);
            if (id == 11) {
                printf("    DEBUG Evento 000011 - Local: '%s'\n", local);
            }
            
            if (fgets(linha, sizeof(linha), arquivo) == NULL) return NULL;
            (*linha_num)++;
            trim_string(linha);
            prioridade = atoi(linha);
            
            printf("    Evento: %s, Local: %s, Duracao_dias: %d, Prioridade: %d\n", 
                    nome_evento, local, duracao, prioridade);
            return evento_criar(id, data, hora, duracao, nome_evento, local, prioridade);
        }
        
        case 'P': {
            char adiavel_str[10];
            char motivo[MAX_STRING];
            char local[MAX_STRING];
            int prioridade;
            
            if (fgets(adiavel_str, sizeof(adiavel_str), arquivo) == NULL) return NULL;
            (*linha_num)++;
            trim_string(adiavel_str);
            bool adiavel = string_para_bool(adiavel_str);
            
            if (fgets(motivo, sizeof(motivo), arquivo) == NULL) return NULL;
            (*linha_num)++;
            trim_string(motivo);
            
            if (fgets(local, sizeof(local), arquivo) == NULL) return NULL;
            (*linha_num)++;
            trim_string(local);
            
            if (fgets(linha, sizeof(linha), arquivo) == NULL) return NULL;
            (*linha_num)++;
            trim_string(linha);
            prioridade = atoi(linha);
            
            printf("    Particular: %s, Local: %s, Adiavel: %d, Prioridade: %d\n", 
                   motivo, local, adiavel, prioridade);
            return particular_criar(id, data, hora, duracao, adiavel, motivo, local, prioridade);
        }
        
        default:
            printf("    Tipo desconhecido: %c\n", tipo);
            return NULL;
    }
}