#ifndef PARSER_H
#define PARSER_H

#include "appointment.h"
#include "list.h"
#include <stdio.h>

int parse_id(const char *s);
void zero_base(Appointment *b, Tipo t, int id);
Appointment *parse_aula(FILE *f, int id);
Appointment *parse_orient(FILE *f, int id);
Appointment *parse_reuniao(FILE *f, int id);
Appointment *parse_evento(FILE *f, int id);
Appointment *parse_particular(FILE *f, int id);
Node *parse_agenda(const char *path);

#endif