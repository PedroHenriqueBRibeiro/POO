#include <stdio.h>
#include <stdlib.h>
#include "../include/common.h"
#include "../include/data/data.h"
#include "../include/data/hora.h"
#include "../include/data/datetime.h"
#include "../include/lista/lista.h"
#include "../include/classes/compromisso.h"
#include "../include/relatorios/gerenciador.h"

int main() {
    printf("SISTEMA DE FILTRO DE COMPROMISSOS\n");
    GerenciadorRelatorios* gerenciador = gerenciador_criar();
    if (gerenciador == NULL) {
        printf("Erro\n");
        return 1;
    }
    printf("Carregando dados...\n");
    gerenciador_carregar_dados(gerenciador, "exemplos/agenda.txt", "exemplos/posicoes.txt");
    if (gerenciador->todos_compromissos == NULL) {
        printf("Erro\n");
        gerenciador_destruir(gerenciador);
        return 1;
    }
    printf("Compromissos carregados: %d\n", lista_tamanho(gerenciador->todos_compromissos));
    gerenciador_gerar_relatorios(gerenciador);
    gerenciador_calcular_resultado(gerenciador);
    gerenciador_destruir(gerenciador);
    printf("Relatórios gerados:\n");
    printf("- relatconfirmados.txt\n");
    printf("- relatadiados.txt\n");
    printf("- relatcancelados.txt\n");
    printf("- relatcompromissos.txt\n");
    printf("- resultado.txt\n");
    
    return 0;
}