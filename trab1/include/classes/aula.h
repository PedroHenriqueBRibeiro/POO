#ifndef AULA_H
#define AULA_H

#include "compromisso.h"

// Construtor específico para Aula
Compromisso* aula_criar(int id, Data data, Hora hora, int duracao_minutos,
                       const char* nome_disciplina, Nivel nivel, int grau_prioridade);

// Função para impressão completa (usada no relatório completo)
void aula_imprimir_completo(Compromisso* aula);

#endif