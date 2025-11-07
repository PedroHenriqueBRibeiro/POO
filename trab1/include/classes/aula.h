#ifndef AULA_H
#define AULA_H

#include "compromisso.h"

Compromisso* aula_criar(int id, Data data, Hora hora, int duracao_minutos,
                       const char* nome_disciplina, Nivel nivel, int grau_prioridade);
void aula_imprimir_completo(Compromisso* aula);

#endif