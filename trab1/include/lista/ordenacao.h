#ifndef ORDENACAO_H
#define ORDENACAO_H

#include "../common.h"

void ordenar_lista(void** array, int tamanho, int (*comparador)(void*, void*));
void bubble_sort(void** array, int tamanho, int (*comparador)(void*, void*));

#endif