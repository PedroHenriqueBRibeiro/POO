#include "../../include/data/datetime.h"
#include <stdio.h>
#include <string.h>

DateTime criar_datetime(Data data, Hora hora) {
    DateTime dt = {data, hora};
    return dt;
}
DateTime ler_datetime(const char* str_data, const char* str_hora) {
    Data data = ler_data(str_data);
    Hora hora = ler_hora(str_hora);
    return criar_datetime(data, hora);
}
void imprimir_datetime(DateTime dt) {
    imprimir_data(dt.data);
    printf(" ");
    imprimir_hora(dt.hora);
}
int comparar_datetime(DateTime dt1, DateTime dt2) {
    int cmp_data = comparar_datas(dt1.data, dt2.data);
    if (cmp_data != 0) return cmp_data;
    return comparar_horas(dt1.hora, dt2.hora);
}

DateTime adicionar_minutos_datetime(DateTime dt, int minutos) {
    DateTime novo_dt = dt;
    novo_dt.hora = adicionar_minutos(dt.hora, minutos);
    if (novo_dt.hora.hora < dt.hora.hora) {
        novo_dt.data.dia++;
    }
    
    return novo_dt;
}

DateTime calcular_fim_compromisso(DateTime inicio, int duracao_minutos) {
    return adicionar_minutos_datetime(inicio, duracao_minutos);
}

int diferenca_minutos_datetime(DateTime dt1, DateTime dt2) {
    return diferenca_minutos(dt1.hora, dt2.hora);
}