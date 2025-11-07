#include "../include/common.h"
#include <string.h>
#include <ctype.h>

void trim_string(char* str) {
    if (str == NULL) return;
    char* end;
    while(isspace((unsigned char)*str)) str++; 
    if(*str == 0) return;
    end = str + strlen(str) - 1;
    while(end > str && isspace((unsigned char)*end)) end--;
    *(end + 1) = '\0';
}
int string_para_int(const char* str) {
    return atoi(str);
}
bool string_para_bool(const char* str) {
    return str != NULL && (strcmp(str, "true") == 0 || strcmp(str, "1") == 0);
}
void formatar_id(int id, char* buffer) {
    if (buffer == NULL) return;
    snprintf(buffer, ID_DIGITOS + 1, "%06d", id);
}
bool arquivo_existe(const char* nome_arquivo) {
    FILE* arquivo = fopen(nome_arquivo, "r");
    if (arquivo != NULL) {
        fclose(arquivo);
        return true;
    }
    return false;
}
FILE* abrir_arquivo_leitura(const char* nome_arquivo) {
    return fopen(nome_arquivo, "r");
}
FILE* abrir_arquivo_escrita(const char* nome_arquivo) {
    return fopen(nome_arquivo, "w");
}