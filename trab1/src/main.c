#include <stdio.h>
#include <stdlib.h>
#include "../include/common.h"
#include "../include/relatorios/gerenciador.h"

int main() {
    printf("=== SISTEMA DE FILTRO DE COMPROMISSOS ===\n");
    printf("Iniciando...\n");
    
    // Cria e configura gerenciador
    GerenciadorRelatorios* gerenciador = gerenciador_criar();
    if (gerenciador == NULL) {
        printf("Erro: Não foi possível criar o gerenciador.\n");
        return 1;
    }
    
    // Carrega dados
    printf("Carregando dados...\n");
    gerenciador_carregar_dados(gerenciador, "exemplos/agenda.txt", "exemplos/posicoes.txt");
    
    if (gerenciador->todos_compromissos == NULL) {
        printf("Erro: Não foi possível carregar os compromissos.\n");
        gerenciador_destruir(gerenciador);
        return 1;
    }
    
    printf("Compromissos carregados: %d\n", lista_tamanho(gerenciador->todos_compromissos));
    
    // Gera relatórios
    printf("Gerando relatórios...\n");
    gerenciador_gerar_relatorios(gerenciador);
    
    // Calcula resultado final
    printf("Calculando resultado final...\n");
    gerenciador_calcular_resultado(gerenciador);
    
    // Limpeza
    gerenciador_destruir(gerenciador);
    
    printf("=== PROCESSAMENTO CONCLUÍDO ===\n");
    printf("Relatórios gerados:\n");
    printf("- relatconfirmados.txt\n");
    printf("- relatadiados.txt\n");
    printf("- relatcancelados.txt\n");
    printf("- relatcompromissos.txt\n");
    printf("- resultado.txt\n");
    
    return 0;
}