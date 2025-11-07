#ifndef ADIADOS_H
#define ADIADOS_H

#include "../common.h"
#include "../classes/compromisso.h"
#include "../lista/lista.h"
#include "tipos.h"
#include "../filtro/prioridade.h"
void adiados_ordenar(Lista* compromissos_adiados);
char* adiados_formatar_linha(CompromissoAdiado* comp_adiado);

#endif