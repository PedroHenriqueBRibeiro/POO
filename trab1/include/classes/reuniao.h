#ifndef REUNIAO_H
#define REUNIAO_H

#include "compromisso.h"

// Construtor específico para Reunião
Compromisso* reuniao_criar(int id, Data data, Hora hora, int duracao_minutos,
                          bool adiavel, const char* assunto, int grau_prioridade);

// Função para impressão completa
void reuniao_imprimir_completo(Compromisso* reuniao);

#endif