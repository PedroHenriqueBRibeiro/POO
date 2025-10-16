#include "../../include/filtro/conflito.h"
#include <stdlib.h>

bool compromissos_conflitam(Compromisso* c1, Compromisso* c2) {
    if (c1 == NULL || c2 == NULL) return false;
    
    // Verifica se é o mesmo compromisso
    if (c1->id == c2->id) return false;
    
    // Verifica se estão no mesmo dia
    if (comparar_datas(c1->data, c2->data) != 0) return false;
    
    // Calcula horário de fim
    Data data_fim1, data_fim2;
    Hora hora_fim1, hora_fim2;
    compromisso_obter_fim(c1, &data_fim1, &hora_fim1);
    compromisso_obter_fim(c2, &data_fim2, &hora_fim2);
    
    // Verifica sobreposição
    DateTime inicio1 = criar_datetime(c1->data, c1->hora);
    DateTime fim1 = criar_datetime(data_fim1, hora_fim1);
    DateTime inicio2 = criar_datetime(c2->data, c2->hora);
    DateTime fim2 = criar_datetime(data_fim2, hora_fim2);
    
    // c1 começa durante c2 OU c2 começa durante c1
    return (comparar_datetime(inicio1, fim2) < 0 && comparar_datetime(fim1, inicio2) > 0) ||
           (comparar_datetime(inicio2, fim1) < 0 && comparar_datetime(fim2, inicio1) > 0);
}

Lista* detectar_todos_conflitos(Lista* compromissos) {
    if (compromissos == NULL) return NULL;
    
    Lista* conflitos = lista_criar();
    if (conflitos == NULL) return NULL;
    
    // TODO: Implementar detecção completa de conflitos
    // Percorre todos os pares de compromissos
    
    return conflitos;
}