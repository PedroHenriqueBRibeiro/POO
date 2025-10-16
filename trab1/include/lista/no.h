#ifndef NO_H
#define NO_H

#include "../common.h"

typedef struct No {
    void* dado;
    struct No* proximo;
    struct No* anterior;
} No;

// Funções do nó
No* no_criar(void* dado);
void no_destruir(No* no);

#endif