#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include "datetime.h"
#include "util.h"

typedef enum { T_AULA = 0, T_ORIENT = 1, T_REUNIAO = 2, T_EVENTO = 3, T_PARTICULAR = 4 } Tipo;

typedef struct AppointmentVTable AppointmentVTable;

typedef struct {
    Tipo tipo; 
    int id;
    DateTime ini, fim; 
    int dur_min;
    int grau_prior; 
    int adiavel;
    char descricao[128];
    int forced_by;
    const AppointmentVTable *vptr;
} Appointment;

struct AppointmentVTable {
    int (*factor)(const Appointment *);
    int (*is_adiavel)(const Appointment *);
    void (*describe)(const Appointment *, char *, size_t);
    void (*data_full)(const Appointment *, char *, size_t);
};

typedef struct { 
    Appointment base; 
    char disciplina[MAX_STR]; 
    char nivel[MAX_STR]; 
} Aula;

typedef struct { 
    Appointment base; 
    char aluno[MAX_STR]; 
    char nivel[MAX_STR]; 
    char assunto[MAX_STR]; 
} Orient;

typedef struct { 
    Appointment base; 
    char assunto[MAX_STR]; 
} Reuniao;

typedef struct { 
    Appointment base; 
    char nome[MAX_STR]; 
    char local[MAX_STR]; 
    int dur_dias; 
} Evento;

typedef struct { 
    Appointment base; 
    char motivo[MAX_STR]; 
    char local[MAX_STR]; 
} Particular;


extern const AppointmentVTable VT_AULA;
extern const AppointmentVTable VT_ORIENT;
extern const AppointmentVTable VT_REUNIAO;
extern const AppointmentVTable VT_EVENTO;
extern const AppointmentVTable VT_PART;

int tipo_rank_for_tiebreak(Tipo t);
int base_factor(Tipo t);
int appt_priority(const Appointment *a);
int appt_is_adiavel(const Appointment *a);
void appt_fill_descricao(Appointment *a);
void dbg_print(const char *tag, const Appointment *a);
void free_appt(void *p);

#endif