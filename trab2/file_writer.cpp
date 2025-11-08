#include "file_writer.h"
#include "sorting.h"
#include "comparators.h"
#include <cstdio>
#include <cstdlib>

void pad_id(int id, char* out) { 
    std::sprintf(out, "%06d", id); 
}

void write_confirmed(const char* path, Appointment** A, int N) {
    msort((void**)A, N, cmp_by_datetime_asc, nullptr);
    std::FILE* f = std::fopen(path, "w"); if (!f) { std::perror("open"); std::exit(1); }
    for (int i = 0; i < N; i++) {
        char d[16], h[16], idb[16]; fmt_date(&A[i]->ini, d); fmt_time(&A[i]->ini, h); pad_id(A[i]->id, idb);
        std::fprintf(f, "%s %s\n%s\n%s", d, h, idb, A[i]->descricao.c_str());
        if (i != N - 1) std::fprintf(f, "\n\n");
    }
    std::fclose(f);
}

void write_delayed(const char* path, Appointment** A, int N) {
    msort((void**)A, N, cmp_by_priority_desc, nullptr);
    std::FILE* f = std::fopen(path, "w"); if (!f) { std::perror("open"); std::exit(1); }
    for (int i = 0; i < N; i++) {
        char idb[16], win[16]; pad_id(A[i]->id, idb); pad_id(A[i]->forced_by, win);
        std::fprintf(f, "%s\n%s\n%d\n%s", idb, A[i]->descricao.c_str(), A[i]->priority(), win);
        if (i != N - 1) std::fprintf(f, "\n\n");
    }
    std::fclose(f);
}

void write_canceled(const char* path, Appointment** A, int N) {
    msort((void**)A, N, cmp_by_duration_asc, nullptr);
    std::FILE* f = std::fopen(path, "w"); if (!f) { std::perror("open"); std::exit(1); }
    for (int i = 0; i < N; i++) {
        char idb[16], win[16]; pad_id(A[i]->id, idb); pad_id(A[i]->forced_by, win);
        std::fprintf(f, "%s\n%s\n%d\n%s", idb, A[i]->descricao.c_str(), A[i]->priority(), win);
        if (i != N - 1) std::fprintf(f, "\n\n");
    }
    std::fclose(f);
}

void write_all(const char* path, Appointment** A, int N) {
    msort((void**)A, N, cmp_by_id_asc, nullptr);
    std::FILE* f = std::fopen(path, "w"); if (!f) { std::perror("open"); std::exit(1); }
    for (int i = 0; i < N; i++) {
        char idb[16], d1[16], h1[16], d2[16], h2[16]; pad_id(A[i]->id, idb);
        fmt_date(&A[i]->ini, d1); fmt_time(&A[i]->ini, h1);
        fmt_date(&A[i]->fim, d2); fmt_time(&A[i]->fim, h2);
        std::fprintf(f, "%s: %s\n", idb, A[i]->descricao.c_str());
        std::fprintf(f, "Início: %s %s\n", d1, h1);
        std::fprintf(f, "Fim: %s %s\n", d2, h2);
        std::fprintf(f, "Prioridade: %d\n", A[i]->priority());
        switch (A[i]->tipo) {
        case Tipo::AULA: { auto* p = (Aula*)A[i]; std::fprintf(f, "Nível: %s", p->nivel.c_str()); } break;
        case Tipo::ORIENT: { auto* p = (Orient*)A[i]; std::fprintf(f, "Nível: %s\nAssunto: %s", p->nivel.c_str(), p->assunto.c_str()); } break;
        case Tipo::REUNIAO: { auto* p = (Reuniao*)A[i]; std::fprintf(f, "Assunto: %s", p->assunto.c_str()); } break;
        case Tipo::EVENTO: { auto* p = (Evento*)A[i]; std::fprintf(f, "Local: %s", p->local.c_str()); } break;
        case Tipo::PARTICULAR: { auto* p = (Particular*)A[i]; std::fprintf(f, "Local: %s", p->local.c_str()); } break;
        }
        if (i != N - 1) std::fprintf(f, "\n\n");
    }
    std::fclose(f);
}