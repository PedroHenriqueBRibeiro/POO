#ifndef CONFIRMADOS_H
#define CONFIRMADOS_H

#include "../common.h"
#include "../classes/compromisso.h"

// Funções específicas do relatório de confirmados
void confirmados_ordenar(Lista* compromissos);
char* confirmados_formatar_linha(Compromisso* comp);

#endif