#include "appointment.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int tipo_rank_for_tiebreak(Tipo t) {
    switch (t) {
        case T_REUNIAO: return 5;
        case T_EVENTO: return 4;
        case T_AULA: return 3;
        case T_PARTICULAR: return 2;
        case T_ORIENT: return 1;
        default: return 0;
    }
}

int base_factor(Tipo t) {
    switch (t) {
        case T_AULA: return 2;
        case T_ORIENT: return 1;
        case T_REUNIAO: return 4;
        case T_EVENTO: return 3;
        case T_PARTICULAR: return 2;
        default: return 1;
    }
}

int appt_priority(const Appointment *a) {
    return a->grau_prior * a->vptr->factor(a);
}

int appt_is_adiavel(const Appointment *a) {
    return a->vptr->is_adiavel(a);
}

void appt_fill_descricao(Appointment *a) {
    a->vptr->describe(a, a->descricao, sizeof(a->descricao));
}

void dbg_print(const char *tag, const Appointment *a) {
    char s1[20], s2[20], idb[8];
    dbg_dt(&a->ini, s1);
    dbg_dt(&a->fim, s2);
    sprintf(idb, "%06d", a->id);
    fprintf(stderr, "[%s] id=%s tipo=%d prio=%d adiavel=%d ini=%s fim=%s desc=%s\n",
            tag, idb, a->tipo, a->grau_prior * a->vptr->factor(a), a->adiavel, s1, s2, a->descricao);
}

void free_appt(void *p) {
    free(p);
}