#ifndef EVENTO_H
#define EVENTO_H

#include "compromisso.h"

// Construtor específico para Evento
Compromisso* evento_criar(int id, Data data, Hora hora, int duracao_dias,
                         const char* nome_evento, const char* local, int grau_prioridade);

// Função para impressão completa
void evento_imprimir_completo(Compromisso* evento);

#endif