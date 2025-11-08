#include "scheduler.h"
#include "sorting.h"
#include "comparators.h"
#include <cstdlib>
#include <cstring>

void buckets_init(Buckets* B) {
    B->confirmed = nullptr;
    B->delayed = nullptr;
    B->canceled = nullptr;
    B->nconf = B->ndel = B->ncanc = 0;
    B->cap_conf = B->cap_del = B->cap_canc = 0;
}

bool overlaps(const Appointment* a, const Appointment* b) {
    return !(cmp_datetime(&a->fim, &b->ini) <= 0 || cmp_datetime(&b->fim, &a->ini) <= 0);
}

bool wins_over(const Appointment* a, const Appointment* b) {
    int pa = a->priority(), pb = b->priority(); if (pa != pb) return pa > pb;
    int c = cmp_datetime(&a->ini, &b->ini); if (c != 0) return c < 0;
    int ra = tipo_rank_for_tiebreak(a->tipo), rb = tipo_rank_for_tiebreak(b->tipo); if (ra != rb) return ra > rb;
    int d = std::strcmp(a->descricao.c_str(), b->descricao.c_str()); if (d != 0) return d < 0;
    return a->id < b->id;
}

static void buckets_push(Appointment*** arr, size_t* n, size_t* cap, Appointment* a) {
    if (*n >= *cap) {
        *cap = (*cap == 0) ? 8 : *cap * 2;
        *arr = (Appointment**)std::realloc(*arr, (*cap) * sizeof(Appointment*));
    }
    (*arr)[(*n)++] = a;
}

void apply_filter(Appointment** A, int N, Buckets* B) {
    buckets_init(B);
    
    std::fprintf(stderr, "[debug] apply_filter: N=%d\n", N);
    if (!A || N <= 0) {
        std::fprintf(stderr, "[debug] apply_filter: nada a fazer\n");
        return;
    }
    msort((void**)A, N, cmp_by_datetime_asc, nullptr);

    int i = 0;
    while (i < N) {
        int j = i;
        while (j + 1 < N) {
            int touch = 0;
            for (int k = i; k <= j; k++) {
                if (overlaps(A[k], A[j + 1])) { touch = 1; break; }
            }
            if (!touch) break;
            j++;
        }

        if (i == j) {
            buckets_push(&B->confirmed, &B->nconf, &B->cap_conf, A[i]);
            i = j + 1;
            continue;
        }

        int gsz = j - i + 1;
        unsigned char* st = (unsigned char*)std::malloc(gsz);
        for (int t = 0; t < gsz; ++t) st[t] = 0;

        while (true) {
            int w = -1;
            for (int t = 0; t < gsz; ++t) {
                if (st[t] == 0) {
                    if (w == -1) w = t;
                    else if (wins_over(A[i + t], A[i + w])) w = t;
                }
            }
            if (w == -1) break;

            buckets_push(&B->confirmed, &B->nconf, &B->cap_conf, A[i + w]);
            st[w] = 1;

            for (int t = 0; t < gsz; ++t) {
                if (t == w || st[t] != 0) continue;
                if (overlaps(A[i + t], A[i + w])) {
                    Appointment* loser = A[i + t];
                    loser->forced_by = A[i + w]->id;
                    if (loser->isAdiavel()) {
                        buckets_push(&B->delayed, &B->ndel, &B->cap_del, loser);
                        st[t] = 2;
                    }
                    else {
                        buckets_push(&B->canceled, &B->ncanc, &B->cap_canc, loser);
                        st[t] = 3;
                    }
                }
            }
        }
        std::free(st);
        i = j + 1;
    }
}