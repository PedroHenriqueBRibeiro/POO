#ifndef DATA_H
#define DATA_H

#include "../common.h"

typedef struct Data {
    int dia;
    int mes;
    int ano;
} Data;
Data criar_data(int dia, int mes, int ano);
Data ler_data(const char* str_data);
void imprimir_data(Data data);
int comparar_datas(Data d1, Data d2);
bool data_valida(Data data);

#endif