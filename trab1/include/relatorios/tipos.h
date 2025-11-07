#ifndef TIPOS_H
#define TIPOS_H
#include "../classes/compromisso.h"
typedef struct {
    Compromisso* compromisso;
    Compromisso* conflitante;
} CompromissoAdiado;

typedef struct {
    Compromisso* compromisso;
    Compromisso* conflitante;
} CompromissoCancelado;

#endif