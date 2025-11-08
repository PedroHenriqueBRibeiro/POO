#include "utils.h"

void trim_newline(char *s) {
    size_t n = std::strlen(s);
    while (n > 0 && (s[n - 1] == '\n' || s[n - 1] == '\r')) {
        s[--n] = '\0';
    }
}

void read_line_req(std::FILE* f, char* buf, size_t cap) {
    if (!std::fgets(buf, (int)cap, f)) {
        std::fprintf(stderr, "Erro: EOF inesperado.\n");
        std::exit(1);
    }
    trim_newline(buf);
}

void ensure_blank_line(std::FILE* f) {
    long pos = std::ftell(f);
    int c = std::fgetc(f);
    if (c == '\r') {
        int c2 = std::fgetc(f);
        if (c2 != '\n') std::fseek(f, pos, SEEK_SET);
    } else if (c == '\n') {
    } else {
        if (c != EOF) std::fseek(f, pos, SEEK_SET);
    }
}

bool is_space(int c) { 
    return c == ' ' || c == '\t' || c == '\r' || c == '\n'; 
}

char* rtrim_inplace(char* s) {
    size_t n = std::strlen(s);
    while (n > 0 && is_space((unsigned char)s[n - 1])) s[--n] = '\0';
    return s;
}

int roman_suffix_value(const char* s, char* base_out, size_t cap) {
    char buf[128];
    std::strncpy(buf, s, sizeof(buf) - 1);
    buf[sizeof(buf) - 1] = '\0';
    rtrim_inplace(buf);
    size_t n = std::strlen(buf);
    if (n == 0) {
        if (base_out) { std::strncpy(base_out, buf, cap); base_out[cap - 1] = 0; }
        return -1;
    }
    size_t p = n;
    while (p > 0 && !is_space((unsigned char)buf[p - 1])) p--;
    const char* last = buf + p;
    char head[128];
    if (p > 0) {
        std::memcpy(head, buf, p - 1);
        head[p - 1] = '\0';
        rtrim_inplace(head);
    } else {
        head[0] = '\0';
    }
    int val = -1;
    if (!std::strcmp(last, "I")) val = 1;
    else if (!std::strcmp(last, "II")) val = 2;
    else if (!std::strcmp(last, "III")) val = 3;
    else if (!std::strcmp(last, "IV")) val = 4;
    else if (!std::strcmp(last, "V")) val = 5;
    else if (!std::strcmp(last, "VI")) val = 6;
    else if (!std::strcmp(last, "VII")) val = 7;
    else if (!std::strcmp(last, "VIII")) val = 8;
    else if (!std::strcmp(last, "IX")) val = 9;
    else if (!std::strcmp(last, "X")) val = 10;

    if (base_out) {
        if (val != -1) {
            std::strncpy(base_out, head, cap); base_out[cap - 1] = 0;
        } else {
            std::strncpy(base_out, buf, cap); base_out[cap - 1] = 0;
        }
    }
    return val;
}

bool is_header_line(const char* s) {
    if (!s) return false;
    size_t n = std::strlen(s);
    if (n != 7) return false;
    char t = s[0];
    if (!(t == 'A' || t == 'O' || t == 'R' || t == 'E' || t == 'P')) return false;
    for (int i = 1; i < 7; ++i) {
        if (!std::isdigit((unsigned char)s[i])) return false;
    }
    return true;
}

int parse_id(const char* s) {
    if (!std::isalpha((unsigned char)s[0])) {
        std::fprintf(stderr, "Tipo inválido: %s\n", s);
        std::exit(1);
    }
    return std::atoi(s + 1);
}

bool parse_bool(const char* s) {
    if (!s) return false;
    while (*s == ' ' || *s == '\t' || *s == '\r' || *s == '\n') s++;
    char buf[32]; size_t i = 0;
    while (*s && i < sizeof(buf) - 1) {
        buf[i++] = (char)std::tolower((unsigned char)*s++);
    }
    buf[i] = '\0';
    return (std::strcmp(buf, "true") == 0 || std::strcmp(buf, "1") == 0 ||
        std::strcmp(buf, "sim") == 0 || std::strcmp(buf, "yes") == 0);
}