#ifndef COMPLETO_H
#define COMPLETO_H

#include "../common.h"
#include "../classes/compromisso.h"

// Funções específicas do relatório completo
void completo_ordenar(Lista* compromissos);
char* completo_formatar_linha(Compromisso* comp);

#endif