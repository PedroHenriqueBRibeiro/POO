#ifndef LISTA_H
#define LISTA_H

#include "../common.h"

// Forward declaration
typedef struct No No;

typedef struct {
    No* inicio;
    No* fim;
    int tamanho;
} Lista;

// Funções da lista genérica
Lista* lista_criar();
void lista_destruir(Lista* lista);
void lista_inserir_fim(Lista* lista, void* dado);
void lista_remover(Lista* lista, void* dado);
void* lista_buscar(Lista* lista, int (*comparador)(void*, void*), void* alvo);
void lista_ordenar(Lista* lista, int (*comparador)(void*, void*));
void lista_iterar(Lista* lista, void (*funcao)(void*));
int lista_tamanho(Lista* lista);
bool lista_vazia(Lista* lista);

#endif