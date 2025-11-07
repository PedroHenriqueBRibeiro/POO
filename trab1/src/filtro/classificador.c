#include "../../include/filtro/classificador.h"
#include "../../include/filtro/conflito.h"
#include "../../include/filtro/prioridade.h"
#include "../../include/relatorios/tipos.h"
#include "../../include/lista/no.h"
#include <stdlib.h>
static bool compromisso_ja_processado(Compromisso* comp, Lista* adiados, Lista* cancelados) {
    No* atual = adiados->inicio;
    while (atual != NULL) {
        CompromissoAdiado* existente = (CompromissoAdiado*)atual->dado;
        if (existente->compromisso->id == comp->id) {
            return true;
        }
        atual = atual->proximo;
    }
    atual = cancelados->inicio;
    while (atual != NULL) {
        CompromissoCancelado* existente = (CompromissoCancelado*)atual->dado;
        if (existente->compromisso->id == comp->id) {
            return true;
        }
        atual = atual->proximo;
    }
    
    return false;
}

ResultadoClassificacao* classificar_compromissos(Lista* todos_compromissos) {
    if (todos_compromissos == NULL) return NULL;
    
    ResultadoClassificacao* resultado = (ResultadoClassificacao*)malloc(sizeof(ResultadoClassificacao));
    if (resultado == NULL) return NULL;
    
    resultado->confirmados = lista_criar();
    resultado->adiados = lista_criar();
    resultado->cancelados = lista_criar();
    
    if (resultado->confirmados == NULL || resultado->adiados == NULL || resultado->cancelados == NULL) {
        classificacao_destruir(resultado);
        return NULL;
    }
    No* atual = todos_compromissos->inicio;
    while (atual != NULL) {
        Compromisso* comp = (Compromisso*)atual->dado;
        lista_inserir_fim(resultado->confirmados, comp);
        atual = atual->proximo;
    }
    Lista* conflitos = detectar_todos_conflitos(todos_compromissos);
    if (conflitos == NULL) {
        return resultado;
    }
    
    printf("=== DETECÇÃO DE CONFLITOS ===\n");
    printf("Total de conflitos encontrados: %d\n", lista_tamanho(conflitos));
    No* conflito_atual = conflitos->inicio;
    while (conflito_atual != NULL) {
        Conflito* conflito = (Conflito*)conflito_atual->dado;
        
        Compromisso* vencedor;
        Compromisso* perdedor;
        if (conflito->prioridade_comp1 >= conflito->prioridade_comp2) {
            vencedor = conflito->comp1;
            perdedor = conflito->comp2;
        } else {
            vencedor = conflito->comp2;
            perdedor = conflito->comp1;
        }
        if (conflito->prioridade_comp1 == conflito->prioridade_comp2) {
            if (comparar_prioridades_com_desempate(conflito->comp1, conflito->comp2) > 0) {
                vencedor = conflito->comp1;
                perdedor = conflito->comp2;
            } else {
                vencedor = conflito->comp2;
                perdedor = conflito->comp1;
            }
        }
        
        printf("Conflito: %06d (%d) vs %06d (%d) -> Vencedor: %06d\n",
               conflito->comp1->id, conflito->prioridade_comp1,
               conflito->comp2->id, conflito->prioridade_comp2,
               vencedor->id);
        if (!compromisso_ja_processado(perdedor, resultado->adiados, resultado->cancelados)) {
            lista_remover(resultado->confirmados, perdedor);
            if (perdedor->adiavel) {
                CompromissoAdiado* adiado = (CompromissoAdiado*)malloc(sizeof(CompromissoAdiado));
                if (adiado != NULL) {
                    adiado->compromisso = perdedor;
                    adiado->conflitante = vencedor;
                    lista_inserir_fim(resultado->adiados, adiado);
                    printf("  -> %06d adiado (conflito com %06d)\n", perdedor->id, vencedor->id);
                }
            } else {
                CompromissoCancelado* cancelado = (CompromissoCancelado*)malloc(sizeof(CompromissoCancelado));
                if (cancelado != NULL) {
                    cancelado->compromisso = perdedor;
                    cancelado->conflitante = vencedor;
                    lista_inserir_fim(resultado->cancelados, cancelado);
                    printf("  -> %06d cancelado (conflito com %06d)\n", perdedor->id, vencedor->id);
                }
            }
        } else {
            printf("  -> %06d já processado, ignorando duplicação\n", perdedor->id);
        }
        
        conflito_atual = conflito_atual->proximo;
    }
    No* conflito_limpar = conflitos->inicio;
    while (conflito_limpar != NULL) {
        No* proximo = conflito_limpar->proximo;
        free(conflito_limpar->dado);
        free(conflito_limpar);
        conflito_limpar = proximo;
    }
    free(conflitos);
    
    printf("=== RESULTADO DA CLASSIFICAÇÃO ===\n");
    printf("Confirmados: %d\n", lista_tamanho(resultado->confirmados));
    printf("Adiados: %d\n", lista_tamanho(resultado->adiados));
    printf("Cancelados: %d\n", lista_tamanho(resultado->cancelados));
    
    return resultado;
}

void classificacao_destruir(ResultadoClassificacao* resultado) {
    if (resultado == NULL) return;
    if (resultado->confirmados != NULL) {
        No* atual = resultado->confirmados->inicio;
        while (atual != NULL) {
            No* proximo = atual->proximo;
            free(atual);
            atual = proximo;
        }
        free(resultado->confirmados);
    }
    
    if (resultado->adiados != NULL) {
        No* atual = resultado->adiados->inicio;
        while (atual != NULL) {
            No* proximo = atual->proximo;
            free(atual->dado);
            free(atual);
            atual = proximo;
        }
        free(resultado->adiados);
    }
    
    if (resultado->cancelados != NULL) {
        No* atual = resultado->cancelados->inicio;
        while (atual != NULL) {
            No* proximo = atual->proximo;
            free(atual->dado);
            free(atual);
            atual = proximo;
        }
        free(resultado->cancelados);
    }
    
    free(resultado);
}

Compromisso* encontrar_conflitante_principal(Compromisso* comp, Lista* compromissos) {
    (void)comp;
    (void)compromissos;
    return NULL;
}