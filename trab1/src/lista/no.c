#include "../../include/lista/no.h"
#include <stdlib.h>

No* no_criar(void* dado) {
    No* novo_no = (No*)malloc(sizeof(No));
    if (novo_no == NULL) return NULL;
    
    novo_no->dado = dado;
    novo_no->proximo = NULL;
    novo_no->anterior = NULL;
    return novo_no;
}

void no_destruir(No* no) {
    if (no != NULL) {
        free(no);
    }
}