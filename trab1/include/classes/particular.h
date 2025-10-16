#ifndef PARTICULAR_H
#define PARTICULAR_H

#include "compromisso.h"

// Construtor específico para Compromisso Particular
Compromisso* particular_criar(int id, Data data, Hora hora, int duracao_minutos,
                             bool adiavel, const char* motivo, const char* local, int grau_prioridade);

// Função para impressão completa
void particular_imprimir_completo(Compromisso* particular);

#endif