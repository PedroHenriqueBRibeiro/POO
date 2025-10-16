#ifndef ORDENACAO_H
#define ORDENACAO_H

#include "../common.h"

// Função de ordenação genérica (deve ser única conforme especificação)
void ordenar_lista(void** array, int tamanho, int (*comparador)(void*, void*));

// Algoritmos de ordenação (internos - bubble sort para simplicidade)
void bubble_sort(void** array, int tamanho, int (*comparador)(void*, void*));

#endif