#ifndef CONFLITO_H
#define CONFLITO_H

#include "../common.h"
#include "../classes/compromisso.h"
#include "../lista/lista.h"
#include "../data/datetime.h"
#include "prioridade.h"
typedef struct Conflito {
    Compromisso* comp1;
    Compromisso* comp2;
    int prioridade_comp1;
    int prioridade_comp2;
} Conflito;

// Funções de detecção de conflitos
bool compromissos_conflitam(Compromisso* c1, Compromisso* c2);
Lista* detectar_todos_conflitos(Lista* compromissos);

#endif