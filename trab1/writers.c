#include "writers.h"
#include "util.h"
#include "sort.h"
#include "comparators.h"
#include <stdlib.h>
#include <stdio.h>

void write_confirmed(const char *path, Appointment **A, int N) {
    msort((void **)A, N, cmp_by_datetime_asc, NULL);
    FILE *f = fopen(path, "w");
    if (!f) {
        perror("open");
        exit(1);
    }
    for (int i = 0; i < N; i++) {
        char d[16], h[16], idb[16];
        fmt_date(&A[i]->ini, d);
        fmt_time(&A[i]->ini, h);
        pad_id(A[i]->id, idb);
        fprintf(f, "%s %s\n%s\n%s", d, h, idb, A[i]->descricao);
        if (i != N - 1) fprintf(f, "\n\n");
    }
    fclose(f);
}

void write_delayed(const char *path, Appointment **A, int N) {
    msort((void **)A, N, cmp_by_priority_desc, NULL);
    FILE *f = fopen(path, "w");
    if (!f) {
        perror("open");
        exit(1);
    }
    for (int i = 0; i < N; i++) {
        char idb[16], win[16];
        pad_id(A[i]->id, idb);
        pad_id(A[i]->forced_by, win);
        fprintf(f, "%s\n%s\n%d\n%s", idb, A[i]->descricao, appt_priority(A[i]), win);
        if (i != N - 1) fprintf(f, "\n\n");
    }
    fclose(f);
}

void write_canceled(const char *path, Appointment **A, int N) {
    msort((void **)A, N, cmp_by_duration_asc, NULL);
    FILE *f = fopen(path, "w");
    if (!f) {
        perror("open");
        exit(1);
    }
    for (int i = 0; i < N; i++) {
        char idb[16], win[16];
        pad_id(A[i]->id, idb);
        pad_id(A[i]->forced_by, win);
        fprintf(f, "%s\n%s\n%d\n%s", idb, A[i]->descricao, appt_priority(A[i]), win);
        if (i != N - 1) fprintf(f, "\n\n");
    }
    fclose(f);
}

void write_all(const char *path, Appointment **A, int N) {
    msort((void **)A, N, cmp_by_id_asc, NULL);
    FILE *f = fopen(path, "w");
    if (!f) {
        perror("open");
        exit(1);
    }
    for (int i = 0; i < N; i++) {
        char idb[16], d1[16], h1[16], d2[16], h2[16];
        pad_id(A[i]->id, idb);
        fmt_date(&A[i]->ini, d1);
        fmt_time(&A[i]->ini, h1);
        fmt_date(&A[i]->fim, d2);
        fmt_time(&A[i]->fim, h2);
        fprintf(f, "%s: %s\n", idb, A[i]->descricao);
        fprintf(f, "Início: %s %s\n", d1, h1);
        fprintf(f, "Fim: %s %s\n", d2, h2);
        fprintf(f, "Prioridade: %d\n", appt_priority(A[i]));
        
        switch (A[i]->tipo) {
            case T_AULA: {
                Aula *p = (Aula *)A[i];
                fprintf(f, "Nível: %s", p->nivel);
            } break;
            case T_ORIENT: {
                Orient *p = (Orient *)A[i];
                fprintf(f, "Nível: %s\nAssunto: %s", p->nivel, p->assunto);
            } break;
            case T_REUNIAO: {
                Reuniao *p = (Reuniao *)A[i];
                fprintf(f, "Assunto: %s", p->assunto);
            } break;
            case T_EVENTO: {
                Evento *p = (Evento *)A[i];
                fprintf(f, "Local: %s", p->local);
            } break;
            case T_PARTICULAR: {
                Particular *p = (Particular *)A[i];
                fprintf(f, "Local: %s", p->local);
            } break;
            default: break;
        }
        if (i != N - 1) fprintf(f, "\n\n");
    }
    fclose(f);
}