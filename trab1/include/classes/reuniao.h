#ifndef REUNIAO_H
#define REUNIAO_H

#include "compromisso.h"
Compromisso* reuniao_criar(int id, Data data, Hora hora, int duracao_minutos,
                          bool adiavel, const char* assunto, int grau_prioridade);

void reuniao_imprimir_completo(Compromisso* reuniao);

#endif