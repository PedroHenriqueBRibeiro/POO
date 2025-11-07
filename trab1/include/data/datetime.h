#ifndef DATETIME_H
#define DATETIME_H

#include "data.h"
#include "hora.h"

typedef struct DateTime {
    Data data;
    Hora hora;
} DateTime;

DateTime criar_datetime(Data data, Hora hora);
DateTime ler_datetime(const char* str_data, const char* str_hora);
void imprimir_datetime(DateTime dt);
int comparar_datetime(DateTime dt1, DateTime dt2);
DateTime adicionar_minutos_datetime(DateTime dt, int minutos);
DateTime calcular_fim_compromisso(DateTime inicio, int duracao_minutos);
int diferenca_minutos_datetime(DateTime dt1, DateTime dt2);

#endif