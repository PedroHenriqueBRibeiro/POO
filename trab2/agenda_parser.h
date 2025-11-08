#ifndef AGENDA_PARSER_H
#define AGENDA_PARSER_H

#include "linked_list.h"

Appointment* parse_aula(std::FILE* f, int id);
Appointment* parse_orient(std::FILE* f, int id);
Appointment* parse_reuniao(std::FILE* f, int id);
Appointment* parse_evento(std::FILE* f, int id);
Appointment* parse_particular(std::FILE* f, int id);
Node* parse_agenda(const char* path);

#endif