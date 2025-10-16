#ifndef ADIADOS_H
#define ADIADOS_H

#include "../common.h"
#include "../classes/compromisso.h"

// Estrutura para compromisso adiado com info do conflito
typedef struct {
    Compromisso* compromisso;
    Compromisso* conflitante; // compromisso que forçou o adiamento
} CompromissoAdiado;

// Funções específicas do relatório de adiados
void adiados_ordenar(Lista* compromissos_adiados);
char* adiados_formatar_linha(CompromissoAdiado* comp_adiado);

#endif