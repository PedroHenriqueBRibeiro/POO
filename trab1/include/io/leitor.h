#ifndef LEITOR_H
#define LEITOR_H

#include "../common.h"
#include "../classes/compromisso.h"
#include "../lista/lista.h"

typedef struct {
    int i;
    int j; 
    int k;
    int m;
} PosicoesRelatorio;

Lista* ler_agenda(const char* nome_arquivo);
PosicoesRelatorio ler_posicoes(const char* nome_arquivo);
Compromisso* parse_compromisso(const char* linha_tipo, FILE* arquivo, int* linha_num);

#endif