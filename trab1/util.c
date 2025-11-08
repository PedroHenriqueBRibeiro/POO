#include "util.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void trim_newline(char *s) {
    size_t n = strlen(s);
    while (n > 0 && (s[n - 1] == '\n' || s[n - 1] == '\r')) {
        s[--n] = '\0';
    }
}

void read_line_req(FILE *f, char *buf, size_t cap) {
    if (!fgets(buf, (int)cap, f)) {
        fprintf(stderr, "Erro: EOF inesperado.\n");
        exit(1);
    }
    trim_newline(buf);
}

void ensure_blank_line(FILE *f) {
    long pos = ftell(f);
    int c = fgetc(f);

    if (c == '\r') {
        int c2 = fgetc(f);
        if (c2 != '\n') {
            fseek(f, pos, SEEK_SET);
        }
    } else if (c == '\n') {
        // ok
    } else {
        if (c != EOF) {
            fseek(f, pos, SEEK_SET);
        }
    }
}

int parse_bool(const char *s) {
    if (!s) return 0;
    while (*s == ' ' || *s == '\t' || *s == '\r' || *s == '\n') s++;
    char buf[32]; size_t i = 0;
    while (*s && i < sizeof(buf) - 1) { 
        buf[i++] = (char)tolower((unsigned char)*s++); 
    }
    buf[i] = '\0';
    return (strcmp(buf, "true") == 0 || strcmp(buf, "1") == 0 || 
            strcmp(buf, "sim") == 0 || strcmp(buf, "yes") == 0);
}

int is_header_line(const char *s) {
    if (!s) return 0;
    size_t n = strlen(s);
    if (n != 7) return 0;
    char t = s[0];
    if (!(t == 'A' || t == 'O' || t == 'R' || t == 'E' || t == 'P')) return 0;
    for (int i = 1; i < 7; ++i) {
        if (!isdigit((unsigned char)s[i])) return 0;
    }
    return 1;
}

void pad_id(int id, char *out) {
    sprintf(out, "%06d", id);
}


static int is_space(int c){ 
    return c==' '||c=='\t'||c=='\r'||c=='\n'; 
}

static char* rtrim_inplace(char* s){
    size_t n = strlen(s);
    while (n>0 && is_space((unsigned char)s[n-1])) s[--n]='\0';
    return s;
}
static int roman_suffix_value_impl(const char* s, char* base_out, size_t cap){
    char buf[128];
    strncpy(buf, s, sizeof(buf)-1);
    buf[sizeof(buf)-1] = '\0';
    rtrim_inplace(buf);

    size_t n = strlen(buf);
    if (n==0) { 
        if(base_out){ 
            strncpy(base_out, buf, cap); 
            base_out[cap-1]=0; 
        } 
        return -1; 
    }

    size_t p = n;
    while (p>0 && !is_space((unsigned char)buf[p-1])) p--;
    const char* last = buf + p;
    char head[128];
    if (p>0){
        memcpy(head, buf, p-1);
        head[p-1] = '\0';
        rtrim_inplace(head);
    }else{
        head[0]='\0';
    }

    int val = -1;
    if      (strcmp(last,"I")==0)    val=1;
    else if (strcmp(last,"II")==0)   val=2;
    else if (strcmp(last,"III")==0)  val=3;
    else if (strcmp(last,"IV")==0)   val=4;
    else if (strcmp(last,"V")==0)    val=5;
    else if (strcmp(last,"VI")==0)   val=6;
    else if (strcmp(last,"VII")==0)  val=7;
    else if (strcmp(last,"VIII")==0) val=8;
    else if (strcmp(last,"IX")==0)   val=9;
    else if (strcmp(last,"X")==0)    val=10;

    if (base_out){
        if (val!=-1) { 
            strncpy(base_out, head, cap); 
            base_out[cap-1]=0; 
        }
        else { 
            strncpy(base_out, buf, cap); 
            base_out[cap-1]=0; 
        }
    }
    return val;
}
int roman_suffix_value(const char* s, char* base_out, size_t cap) {
    return roman_suffix_value_impl(s, base_out, cap);
}