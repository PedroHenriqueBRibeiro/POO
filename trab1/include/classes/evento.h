#ifndef EVENTO_H
#define EVENTO_H

#include "compromisso.h"
Compromisso* evento_criar(int id, Data data, Hora hora, int duracao_dias,
                         const char* nome_evento, const char* local, int grau_prioridade);
void evento_imprimir_completo(Compromisso* evento);

#endif