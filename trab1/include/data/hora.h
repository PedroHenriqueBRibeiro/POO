#ifndef HORA_H
#define HORA_H

#include "../common.h"

typedef struct {
    int hora;
    int minuto;
} Hora;

// Funções para Hora
Hora criar_hora(int hora, int minuto);
Hora ler_hora(const char* str_hora);
void imprimir_hora(Hora hora);
int comparar_horas(Hora h1, Hora h2);
bool hora_valida(Hora hora);
Hora adicionar_minutos(Hora hora, int minutos);
int diferenca_minutos(Hora h1, Hora h2);

#endif