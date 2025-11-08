#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>

#define MAX_STR 64
#define ID_WIDTH 6

void trim_newline(char *s);
void read_line_req(FILE *f, char *buf, size_t cap);
void ensure_blank_line(FILE *f);
int parse_bool(const char *s);
int is_header_line(const char *s);
void pad_id(int id, char *out);
int roman_suffix_value(const char* s, char* base_out, size_t cap);

#endif