#ifndef GERENCIADOR_H
#define GERENCIADOR_H

#include "../common.h"
#include "../classes/compromisso.h"
#include "../lista/lista.h"
#include "../io/leitor.h"

// Gerenciador principal dos relatórios
typedef struct {
    Lista* todos_compromissos;
    Lista* confirmados;
    Lista* adiados;
    Lista* cancelados;
    PosicoesRelatorio posicoes;
} GerenciadorRelatorios;

// Funções do gerenciador
GerenciadorRelatorios* gerenciador_criar();
void gerenciador_carregar_dados(GerenciadorRelatorios* gerenciador, 
                               const char* agenda_path, const char* posicoes_path);
void gerenciador_gerar_relatorios(GerenciadorRelatorios* gerenciador);
void gerenciador_calcular_resultado(GerenciadorRelatorios* gerenciador);
void gerenciador_destruir(GerenciadorRelatorios* gerenciador);

#endif