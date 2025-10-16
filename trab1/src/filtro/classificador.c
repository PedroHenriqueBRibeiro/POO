#include "../../include/filtro/classificador.h"
#include <stdlib.h>

ResultadoClassificacao* classificar_compromissos(Lista* todos_compromissos) {
    if (todos_compromissos == NULL) return NULL;
    
    ResultadoClassificacao* resultado = (ResultadoClassificacao*)malloc(sizeof(ResultadoClassificacao));
    if (resultado == NULL) return NULL;
    
    resultado->confirmados = lista_criar();
    resultado->adiados = lista_criar();
    resultado->cancelados = lista_criar();
    
    if (resultado->confirmados == NULL || resultado->adiados == NULL || resultado->cancelados == NULL) {
        classificacao_destruir(resultado);
        return NULL;
    }
    
    // TODO: Implementar lógica completa de classificação
    // Por enquanto, coloca todos como confirmados
    No* atual = todos_compromissos->inicio;
    while (atual != NULL) {
        lista_inserir_fim(resultado->confirmados, atual->dado);
        atual = atual->proximo;
    }
    
    return resultado;
}

void classificacao_destruir(ResultadoClassificacao* resultado) {
    if (resultado == NULL) return;
    
    if (resultado->confirmados != NULL) lista_destruir(resultado->confirmados);
    if (resultado->adiados != NULL) lista_destruir(resultado->adiados);
    if (resultado->cancelados != NULL) lista_destruir(resultado->cancelados);
    
    free(resultado);
}

Compromisso* encontrar_conflitante_principal(Compromisso* comp, Lista* compromissos) {
    if (comp == NULL || compromissos == NULL) return NULL;
    
    // TODO: Implementar busca pelo compromisso conflitante com maior prioridade
    return NULL;
}