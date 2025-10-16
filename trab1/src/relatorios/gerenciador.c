#include "../../include/relatorios/gerenciador.h"
#include "../../include/filtro/classificador.h"
#include <stdlib.h>

GerenciadorRelatorios* gerenciador_criar() {
    GerenciadorRelatorios* gerenciador = (GerenciadorRelatorios*)malloc(sizeof(GerenciadorRelatorios));
    if (gerenciador == NULL) return NULL;
    
    gerenciador->todos_compromissos = NULL;
    gerenciador->confirmados = NULL;
    gerenciador->adiados = NULL;
    gerenciador->cancelados = NULL;
    gerenciador->posicoes = (PosicoesRelatorio){0, 0, 0, 0};
    
    return gerenciador;
}

void gerenciador_carregar_dados(GerenciadorRelatorios* gerenciador, 
                               const char* agenda_path, const char* posicoes_path) {
    if (gerenciador == NULL) return;
    
    // Carrega compromissos
    gerenciador->todos_compromissos = ler_agenda(agenda_path);
    
    // Carrega posições
    gerenciador->posicoes = ler_posicoes(posicoes_path);
}

void gerenciador_gerar_relatorios(GerenciadorRelatorios* gerenciador) {
    if (gerenciador == NULL || gerenciador->todos_compromissos == NULL) return;
    
    // Classifica compromissos
    ResultadoClassificacao* classificacao = classificar_compromissos(gerenciador->todos_compromissos);
    if (classificacao == NULL) return;
    
    gerenciador->confirmados = classificacao->confirmados;
    gerenciador->adiados = classificacao->adiados;
    gerenciador->cancelados = classificacao->cancelados;
    
    // Gera relatórios
    escrever_relatorio_confirmados(gerenciador->confirmados, "relatconfirmados.txt");
    escrever_relatorio_adiados(gerenciador->adiados, "relatadiados.txt");
    escrever_relatorio_cancelados(gerenciador->cancelados, "relatcancelados.txt");
    escrever_relatorio_completo(gerenciador->todos_compromissos, "relatcompromissos.txt");
    
    free(classificacao);
}

void gerenciador_calcular_resultado(GerenciadorRelatorios* gerenciador) {
    if (gerenciador == NULL) return;
    
    // TODO: Implementar cálculo do resultado final
    int resultado = 0;
    escrever_resultado(resultado, "resultado.txt");
}

void gerenciador_destruir(GerenciadorRelatorios* gerenciador) {
    if (gerenciador == NULL) return;
    
    if (gerenciador->todos_compromissos != NULL) lista_destruir(gerenciador->todos_compromissos);
    if (gerenciador->confirmados != NULL) lista_destruir(gerenciador->confirmados);
    if (gerenciador->adiados != NULL) lista_destruir(gerenciador->adiados);
    if (gerenciador->cancelados != NULL) lista_destruir(gerenciador->cancelados);
    
    free(gerenciador);
}