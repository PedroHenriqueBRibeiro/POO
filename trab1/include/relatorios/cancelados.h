#ifndef CANCELADOS_H
#define CANCELADOS_H

#include "../common.h"
#include "../classes/compromisso.h"
#include "../lista/lista.h"
#include "tipos.h"
#include "../filtro/prioridade.h"
void cancelados_ordenar(Lista* compromissos_cancelados);
char* cancelados_formatar_linha(CompromissoCancelado* comp_cancelado);

#endif