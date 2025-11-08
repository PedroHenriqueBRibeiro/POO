#ifndef UTILS_H
#define UTILS_H

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <string>

void trim_newline(char *s);
void read_line_req(std::FILE* f, char* buf, size_t cap);
void ensure_blank_line(std::FILE* f);
bool is_space(int c);
char* rtrim_inplace(char* s);
int roman_suffix_value(const char* s, char* base_out, size_t cap);
bool is_header_line(const char* s);
int parse_id(const char* s);
bool parse_bool(const char* s);

#endif