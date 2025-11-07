#ifndef ORIENTACAO_H
#define ORIENTACAO_H

#include "compromisso.h"

Compromisso* orientacao_criar(int id, Data data, Hora hora, int duracao_minutos,
                             bool adiavel, const char* nome_orientado, Nivel nivel,
                             Data data_defesa, Hora hora_defesa, int grau_prioridade);

void orientacao_imprimir_completo(Compromisso* orientacao);

#endif