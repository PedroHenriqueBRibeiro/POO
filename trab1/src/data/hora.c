#include "../../include/data/hora.h"
#include <stdio.h>
#include <string.h>

Hora criar_hora(int hora, int minuto) {
    Hora h = {hora, minuto};
    return h;
}

Hora ler_hora(const char* str_hora) {
    Hora hora = {0, 0};
    if (str_hora == NULL) return hora;
    
    sscanf(str_hora, "%d:%d", &hora.hora, &hora.minuto);
    return hora;
}

void imprimir_hora(Hora hora) {
    printf("%02d:%02d", hora.hora, hora.minuto);
}

int comparar_horas(Hora h1, Hora h2) {
    if (h1.hora != h2.hora) return h1.hora - h2.hora;
    return h1.minuto - h2.minuto;
}

bool hora_valida(Hora hora) {
    return hora.hora >= 0 && hora.hora < 24 && 
           hora.minuto >= 0 && hora.minuto < 60;
}

Hora adicionar_minutos(Hora hora, int minutos) {
    int total_minutos = hora.hora * 60 + hora.minuto + minutos;
    Hora nova_hora = {
        (total_minutos / 60) % 24,
        total_minutos % 60
    };
    return nova_hora;
}

int diferenca_minutos(Hora h1, Hora h2) {
    return (h1.hora * 60 + h1.minuto) - (h2.hora * 60 + h2.minuto);
}