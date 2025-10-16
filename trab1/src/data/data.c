#include "../../include/data/data.h"
#include <stdio.h>
#include <string.h>

Data criar_data(int dia, int mes, int ano) {
    Data data = {dia, mes, ano};
    return data;
}

Data ler_data(const char* str_data) {
    Data data = {0, 0, 0};
    if (str_data == NULL) return data;
    
    sscanf(str_data, "%d/%d/%d", &data.dia, &data.mes, &data.ano);
    return data;
}

void imprimir_data(Data data) {
    printf("%02d/%02d/%04d", data.dia, data.mes, data.ano);
}

int comparar_datas(Data d1, Data d2) {
    if (d1.ano != d2.ano) return d1.ano - d2.ano;
    if (d1.mes != d2.mes) return d1.mes - d2.mes;
    return d1.dia - d2.dia;
}

bool data_valida(Data data) {
    if (data.mes < 1 || data.mes > 12) return false;
    if (data.dia < 1) return false;
    
    // Dias por mês (simplificado - não considera anos bissextos)
    int dias_por_mes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return data.dia <= dias_por_mes[data.mes - 1];
}