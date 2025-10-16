#ifndef LEITOR_H
#define LEITOR_H

#include "../common.h"
#include "../classes/compromisso.h"
#include "../lista/lista.h"

// Estrutura para posições do arquivo posicoes.txt
typedef struct {
    int i; // posição confirmados
    int j; // posição adiados  
    int k; // posição cancelados
    int m; // posição completo
} PosicoesRelatorio;

// Funções de leitura
Lista* ler_agenda(const char* nome_arquivo);
PosicoesRelatorio ler_posicoes(const char* nome_arquivo);
Compromisso* parse_compromisso(const char* linha_tipo, FILE* arquivo);

#endif