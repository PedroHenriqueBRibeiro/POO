#ifndef CONFIRMADOS_H
#define CONFIRMADOS_H

#include "../common.h"
#include "../classes/compromisso.h"
#include "../lista/lista.h"
#include "../data/datetime.h"
void confirmados_ordenar(Lista* compromissos);
char* confirmados_formatar_linha(Compromisso* comp);

#endif