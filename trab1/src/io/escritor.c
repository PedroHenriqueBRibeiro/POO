#include "../../include/io/escritor.h"
#include "../../include/relatorios/confirmados.h"
#include "../../include/relatorios/adiados.h"
#include "../../include/relatorios/cancelados.h"
#include "../../include/relatorios/completo.h"
#include <stdio.h>

void escrever_relatorio_confirmados(Lista* compromissos, const char* nome_arquivo) {
    FILE* arquivo = fopen(nome_arquivo, "w");
    if (arquivo == NULL) return;
    
    // Ordena compromissos
    confirmados_ordenar(compromissos);
    
    // Escreve cada compromisso
    No* atual = compromissos->inicio;
    while (atual != NULL) {
        Compromisso* comp = (Compromisso*)atual->dado;
        char* linha = confirmados_formatar_linha(comp);
        if (linha != NULL) {
            fprintf(arquivo, "%s\n", linha);
        }
        atual = atual->proximo;
    }
    
    fclose(arquivo);
}

// Padrão similar para os outros relatórios...
void escrever_relatorio_adiados(Lista* compromissos, const char* nome_arquivo) {
    FILE* arquivo = fopen(nome_arquivo, "w");
    if (arquivo == NULL) return;
    
    adiados_ordenar(compromissos);
    
    No* atual = compromissos->inicio;
    while (atual != NULL) {
        CompromissoAdiado* comp_adiado = (CompromissoAdiado*)atual->dado;
        char* linha = adiados_formatar_linha(comp_adiado);
        if (linha != NULL) {
            fprintf(arquivo, "%s\n", linha);
        }
        atual = atual->proximo;
    }
    
    fclose(arquivo);
}

void escrever_relatorio_cancelados(Lista* compromissos, const char* nome_arquivo) {
    FILE* arquivo = fopen(nome_arquivo, "w");
    if (arquivo == NULL) return;
    
    cancelados_ordenar(compromissos);
    
    No* atual = compromissos->inicio;
    while (atual != NULL) {
        CompromissoCancelado* comp_cancelado = (CompromissoCancelado*)atual->dado;
        char* linha = cancelados_formatar_linha(comp_cancelado);
        if (linha != NULL) {
            fprintf(arquivo, "%s\n", linha);
        }
        atual = atual->proximo;
    }
    
    fclose(arquivo);
}

void escrever_relatorio_completo(Lista* compromissos, const char* nome_arquivo) {
    FILE* arquivo = fopen(nome_arquivo, "w");
    if (arquivo == NULL) return;
    
    completo_ordenar(compromissos);
    
    No* atual = compromissos->inicio;
    while (atual != NULL) {
        Compromisso* comp = (Compromisso*)atual->dado;
        char* linha = completo_formatar_linha(comp);
        if (linha != NULL) {
            fprintf(arquivo, "%s\n\n", linha);
        }
        atual = atual->proximo;
    }
    
    fclose(arquivo);
}