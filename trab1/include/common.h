#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// Constantes
#define MAX_STRING 51
#define MAX_LINE 256
#define ID_DIGITOS 6

// Tipos de compromisso
typedef enum {
    AULA,
    ORIENTACAO,
    REUNIAO,
    EVENTO,
    PARTICULAR
} TipoCompromisso;

// Funções utilitárias
void trim_string(char* str);
int string_para_int(const char* str);
bool string_para_bool(const char* str);
void formatar_id(int id, char* buffer);

// Manipulação de arquivos
bool arquivo_existe(const char* nome_arquivo);
FILE* abrir_arquivo_leitura(const char* nome_arquivo);
FILE* abrir_arquivo_escrita(const char* nome_arquivo);

#endif