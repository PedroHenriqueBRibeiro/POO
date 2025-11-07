#ifndef PRIORIDADE_H
#define PRIORIDADE_H

#include "../common.h"
#include "../classes/compromisso.h"
#include "../data/datetime.h"

int calcular_prioridade_final(Compromisso* comp);
int comparar_prioridades(Compromisso* c1, Compromisso* c2);
int comparar_prioridades_com_desempate(Compromisso* c1, Compromisso* c2);
const char* obter_nome_tipo_prioridade(TipoCompromisso tipo);

#endif