#ifndef ESCRITOR_H
#define ESCRITOR_H

#include "../common.h"
#include "../classes/compromisso.h"
#include "../lista/lista.h"

// Funções de escrita
void escrever_relatorio_confirmados(Lista* compromissos, const char* nome_arquivo);
void escrever_relatorio_adiados(Lista* compromissos, const char* nome_arquivo);
void escrever_relatorio_cancelados(Lista* compromissos, const char* nome_arquivo);
void escrever_relatorio_completo(Lista* compromissos, const char* nome_arquivo);
void escrever_resultado(int resultado, const char* nome_arquivo);

#endif