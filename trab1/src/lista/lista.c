#include "../../include/lista/lista.h"
#include <stdlib.h>

Lista* lista_criar() {
    Lista* lista = (Lista*)malloc(sizeof(Lista));
    if (lista == NULL) return NULL;
    
    lista->inicio = NULL;
    lista->fim = NULL;
    lista->tamanho = 0;
    return lista;
}

void lista_destruir(Lista* lista) {
    if (lista == NULL) return;
    
    No* atual = lista->inicio;
    while (atual != NULL) {
        No* proximo = atual->proximo;
        no_destruir(atual);
        atual = proximo;
    }
    free(lista);
}

void lista_inserir_fim(Lista* lista, void* dado) {
    if (lista == NULL || dado == NULL) return;
    
    No* novo_no = no_criar(dado);
    if (novo_no == NULL) return;
    
    if (lista->inicio == NULL) {
        lista->inicio = novo_no;
        lista->fim = novo_no;
    } else {
        lista->fim->proximo = novo_no;
        novo_no->anterior = lista->fim;
        lista->fim = novo_no;
    }
    lista->tamanho++;
}

void lista_remover(Lista* lista, void* dado) {
    if (lista == NULL || dado == NULL) return;
    
    No* atual = lista->inicio;
    while (atual != NULL) {
        if (atual->dado == dado) {
            if (atual->anterior != NULL) {
                atual->anterior->proximo = atual->proximo;
            } else {
                lista->inicio = atual->proximo;
            }
            
            if (atual->proximo != NULL) {
                atual->proximo->anterior = atual->anterior;
            } else {
                lista->fim = atual->anterior;
            }
            
            no_destruir(atual);
            lista->tamanho--;
            return;
        }
        atual = atual->proximo;
    }
}

void* lista_buscar(Lista* lista, int (*comparador)(void*, void*), void* alvo) {
    if (lista == NULL || comparador == NULL) return NULL;
    
    No* atual = lista->inicio;
    while (atual != NULL) {
        if (comparador(atual->dado, alvo) == 0) {
            return atual->dado;
        }
        atual = atual->proximo;
    }
    return NULL;
}

void lista_ordenar(Lista* lista, int (*comparador)(void*, void*)) {
    if (lista == NULL || comparador == NULL || lista->tamanho < 2) return;
    
    // Converte lista para array para ordenação
    void** array = (void**)malloc(lista->tamanho * sizeof(void*));
    if (array == NULL) return;
    
    No* atual = lista->inicio;
    for (int i = 0; i < lista->tamanho; i++) {
        array[i] = atual->dado;
        atual = atual->proximo;
    }
    
    // Ordena o array
    ordenar_lista(array, lista->tamanho, comparador);
    
    // Reconstrói a lista ordenada
    atual = lista->inicio;
    for (int i = 0; i < lista->tamanho; i++) {
        atual->dado = array[i];
        atual = atual->proximo;
    }
    
    free(array);
}

void lista_iterar(Lista* lista, void (*funcao)(void*)) {
    if (lista == NULL || funcao == NULL) return;
    
    No* atual = lista->inicio;
    while (atual != NULL) {
        funcao(atual->dado);
        atual = atual->proximo;
    }
}

int lista_tamanho(Lista* lista) {
    return lista != NULL ? lista->tamanho : 0;
}

bool lista_vazia(Lista* lista) {
    return lista == NULL || lista->tamanho == 0;
}