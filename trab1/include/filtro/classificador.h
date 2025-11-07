#ifndef CLASSIFICADOR_H
#define CLASSIFICADOR_H

#include "../common.h"
#include "../classes/compromisso.h"
#include "../lista/lista.h"
#include "conflito.h"
#include "../relatorios/tipos.h"
typedef struct {
    Lista* confirmados;
    Lista* adiados;
    Lista* cancelados;
} ResultadoClassificacao;

ResultadoClassificacao* classificar_compromissos(Lista* todos_compromissos);
void classificacao_destruir(ResultadoClassificacao* resultado);
Compromisso* encontrar_conflitante_principal(Compromisso* comp, Lista* compromissos);

#endif