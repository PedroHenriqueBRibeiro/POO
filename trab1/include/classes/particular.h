#ifndef PARTICULAR_H
#define PARTICULAR_H

#include "compromisso.h"

Compromisso* particular_criar(int id, Data data, Hora hora, int duracao_minutos,
                             bool adiavel, const char* motivo, const char* local, int grau_prioridade);

void particular_imprimir_completo(Compromisso* particular);

#endif