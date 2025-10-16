#include "../../include/lista/ordenacao.h"
#include <stdlib.h>
#include <string.h>

void ordenar_lista(void** array, int tamanho, int (*comparador)(void*, void*)) {
    if (array == NULL || comparador == NULL || tamanho < 2) return;
    
    // Usa bubble sort conforme especificação (único algoritmo de ordenação)
    bubble_sort(array, tamanho, comparador);
}

void bubble_sort(void** array, int tamanho, int (*comparador)(void*, void*)) {
    for (int i = 0; i < tamanho - 1; i++) {
        for (int j = 0; j < tamanho - i - 1; j++) {
            if (comparador(array[j], array[j + 1]) > 0) {
                // Troca os elementos
                void* temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}