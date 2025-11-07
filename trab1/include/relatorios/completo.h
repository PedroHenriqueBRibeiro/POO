#ifndef COMPLETO_H
#define COMPLETO_H

#include "../common.h"
#include "../classes/compromisso.h"
#include "../lista/lista.h"
#include "../data/datetime.h"
#include "../filtro/prioridade.h"
void completo_ordenar(Lista* compromissos);
char* completo_formatar_linha(Compromisso* comp);

#endif