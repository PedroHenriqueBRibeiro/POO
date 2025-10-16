#ifndef CANCELADOS_H
#define CANCELADOS_H

#include "../common.h"
#include "../classes/compromisso.h"

// Estrutura para compromisso cancelado com info do conflito
typedef struct {
    Compromisso* compromisso;
    Compromisso* conflitante; // compromisso que forçou o cancelamento
} CompromissoCancelado;

// Funções específicas do relatório de cancelados
void cancelados_ordenar(Lista* compromissos_cancelados);
char* cancelados_formatar_linha(CompromissoCancelado* comp_cancelado);

#endif