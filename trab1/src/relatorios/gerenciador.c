#include "../../include/relatorios/gerenciador.h"
#include "../../include/filtro/classificador.h"
#include "../../include/lista/no.h"
#include "../../include/io/escritor.h"
#include "../../include/relatorios/tipos.h"
#include "../../include/relatorios/confirmados.h"
#include "../../include/relatorios/adiados.h"
#include "../../include/relatorios/cancelados.h"
#include "../../include/relatorios/completo.h"

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
    gerenciador->todos_compromissos = ler_agenda(agenda_path);
    gerenciador->posicoes = ler_posicoes(posicoes_path);
}

void gerenciador_gerar_relatorios(GerenciadorRelatorios* gerenciador) {
    if (gerenciador == NULL || gerenciador->todos_compromissos == NULL) return;
    ResultadoClassificacao* classificacao = classificar_compromissos(gerenciador->todos_compromissos);
    if (classificacao == NULL) return;
    
    gerenciador->confirmados = classificacao->confirmados;
    gerenciador->adiados = classificacao->adiados;
    gerenciador->cancelados = classificacao->cancelados;
    free(classificacao);
    escrever_relatorio_confirmados(gerenciador->confirmados, "relatconfirmados.txt");
    escrever_relatorio_adiados(gerenciador->adiados, "relatadiados.txt");
    escrever_relatorio_cancelados(gerenciador->cancelados, "relatcancelados.txt");
    escrever_relatorio_completo(gerenciador->todos_compromissos, "relatcompromissos.txt");
}

void gerenciador_calcular_resultado(GerenciadorRelatorios* gerenciador) {
    if (gerenciador == NULL) return;
    
    int resultado = 0;
    
    printf("=== CÁLCULO DETALHADO DO RESULTADO ===\n");
    printf("Ordenando listas...\n");
    if (gerenciador->confirmados != NULL) {
        printf("Confirmados antes da ordenação: ");
        No* atual = gerenciador->confirmados->inicio;
        while (atual != NULL) {
            Compromisso* comp = (Compromisso*)atual->dado;
            printf("%06d ", comp->id);
            atual = atual->proximo;
        }
        printf("\n");
        
        confirmados_ordenar(gerenciador->confirmados);
        
        printf("Confirmados após ordenação: ");
        atual = gerenciador->confirmados->inicio;
        while (atual != NULL) {
            Compromisso* comp = (Compromisso*)atual->dado;
            printf("%06d ", comp->id);
            atual = atual->proximo;
        }
        printf("\n");
    }
    if (gerenciador->adiados != NULL) {
        printf("Adiados antes da ordenação: ");
        No* atual = gerenciador->adiados->inicio;
        while (atual != NULL) {
            CompromissoAdiado* comp = (CompromissoAdiado*)atual->dado;
            printf("%06d(%d) ", comp->compromisso->id, calcular_prioridade_final(comp->compromisso));
            atual = atual->proximo;
        }
        printf("\n");
        
        adiados_ordenar(gerenciador->adiados);
        
        printf("Adiados após ordenação: ");
        atual = gerenciador->adiados->inicio;
        while (atual != NULL) {
            CompromissoAdiado* comp = (CompromissoAdiado*)atual->dado;
            printf("%06d(%d) ", comp->compromisso->id, calcular_prioridade_final(comp->compromisso));
            atual = atual->proximo;
        }
        printf("\n");
    }
    if (gerenciador->cancelados != NULL) {
        printf("Cancelados antes da ordenação: ");
        No* atual = gerenciador->cancelados->inicio;
        while (atual != NULL) {
            CompromissoCancelado* comp = (CompromissoCancelado*)atual->dado;
            printf("%06d(%d) ", comp->compromisso->id, comp->compromisso->duracao_minutos);
            atual = atual->proximo;
        }
        printf("\n");
        
        cancelados_ordenar(gerenciador->cancelados);
        
        printf("Cancelados após ordenação: ");
        atual = gerenciador->cancelados->inicio;
        while (atual != NULL) {
            CompromissoCancelado* comp = (CompromissoCancelado*)atual->dado;
            printf("%06d(%d) ", comp->compromisso->id, comp->compromisso->duracao_minutos);
            atual = atual->proximo;
        }
        printf("\n");
    }
    if (gerenciador->todos_compromissos != NULL) {
        printf("Completo antes da ordenação: ");
        No* atual = gerenciador->todos_compromissos->inicio;
        while (atual != NULL) {
            Compromisso* comp = (Compromisso*)atual->dado;
            printf("%06d ", comp->id);
            atual = atual->proximo;
        }
        printf("\n");
        
        completo_ordenar(gerenciador->todos_compromissos);
        
        printf("Completo após ordenação: ");
        atual = gerenciador->todos_compromissos->inicio;
        while (atual != NULL) {
            Compromisso* comp = (Compromisso*)atual->dado;
            printf("%06d ", comp->id);
            atual = atual->proximo;
        }
        printf("\n");
    }
    if (gerenciador->confirmados != NULL && gerenciador->posicoes.i > 0) {
        int contador = 1;
        No* atual = gerenciador->confirmados->inicio;
        while (atual != NULL && contador < gerenciador->posicoes.i) {
            atual = atual->proximo;
            contador++;
        }
        if (atual != NULL) {
            Compromisso* comp = (Compromisso*)atual->dado;
            resultado += comp->duracao_minutos;
            printf("i=%d: ID=%06d, Duracao=%d\n", 
                   gerenciador->posicoes.i, comp->id, comp->duracao_minutos);
        } else {
            printf("ERRO: i=%d não encontrado\n", gerenciador->posicoes.i);
        }
    }
    if (gerenciador->adiados != NULL && gerenciador->posicoes.j > 0) {
        int contador = 1;
        No* atual = gerenciador->adiados->inicio;
        while (atual != NULL && contador < gerenciador->posicoes.j) {
            atual = atual->proximo;
            contador++;
        }
        if (atual != NULL) {
            CompromissoAdiado* comp_adiado = (CompromissoAdiado*)atual->dado;
            resultado += comp_adiado->compromisso->duracao_minutos;
            printf("j=%d: ID=%06d, Duracao=%d\n", 
                   gerenciador->posicoes.j, comp_adiado->compromisso->id, 
                   comp_adiado->compromisso->duracao_minutos);
        } else {
            printf("ERRO: j=%d não encontrado\n", gerenciador->posicoes.j);
        }
    }
    if (gerenciador->cancelados != NULL && gerenciador->posicoes.k > 0) {
        int contador = 1;
        No* atual = gerenciador->cancelados->inicio;
        while (atual != NULL && contador < gerenciador->posicoes.k) {
            atual = atual->proximo;
            contador++;
        }
        if (atual != NULL) {
            CompromissoCancelado* comp_cancelado = (CompromissoCancelado*)atual->dado;
            resultado += comp_cancelado->compromisso->duracao_minutos;
            printf("k=%d: ID=%06d, Duracao=%d\n", 
                   gerenciador->posicoes.k, comp_cancelado->compromisso->id,
                   comp_cancelado->compromisso->duracao_minutos);
        } else {
            printf("ERRO: k=%d não encontrado\n", gerenciador->posicoes.k);
        }
    }
    if (gerenciador->todos_compromissos != NULL && gerenciador->posicoes.m > 0) {
        int contador = 1;
        No* atual = gerenciador->todos_compromissos->inicio;
        while (atual != NULL && contador < gerenciador->posicoes.m) {
            atual = atual->proximo;
            contador++;
        }
        if (atual != NULL) {
            Compromisso* comp = (Compromisso*)atual->dado;
            resultado += comp->duracao_minutos;
            printf("m=%d: ID=%06d, Duracao=%d\n", 
                   gerenciador->posicoes.m, comp->id, comp->duracao_minutos);
        } else {
            printf("ERRO: m=%d não encontrado\n", gerenciador->posicoes.m);
        }
    }
    
    printf("Resultado calculado: %d\n", resultado);
    escrever_resultado(resultado, "resultado.txt");
}

void gerenciador_destruir(GerenciadorRelatorios* gerenciador) {
    if (gerenciador == NULL) return;
    
    if (gerenciador->todos_compromissos != NULL) {
        No* atual = gerenciador->todos_compromissos->inicio;
        while (atual != NULL) {
            No* proximo = atual->proximo;
            compromisso_destruir((Compromisso*)atual->dado);
            free(atual);
            atual = proximo;
        }
        free(gerenciador->todos_compromissos);
    }
    
    if (gerenciador->confirmados != NULL) {
        No* atual = gerenciador->confirmados->inicio;
        while (atual != NULL) {
            No* proximo = atual->proximo;
            free(atual);
            atual = proximo;
        }
        free(gerenciador->confirmados);
    }
    
    if (gerenciador->adiados != NULL) {
        No* atual = gerenciador->adiados->inicio;
        while (atual != NULL) {
            No* proximo = atual->proximo;
            free(atual->dado);
            free(atual);
            atual = proximo;
        }
        free(gerenciador->adiados);
    }
    
    if (gerenciador->cancelados != NULL) {
        No* atual = gerenciador->cancelados->inicio;
        while (atual != NULL) {
            No* proximo = atual->proximo;
            free(atual->dado);
            free(atual);
            atual = proximo;
        }
        free(gerenciador->cancelados);
    }
    
    free(gerenciador);
}