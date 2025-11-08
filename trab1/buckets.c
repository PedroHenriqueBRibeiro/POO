#include "buckets.h"
#include "comparators.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void buckets_init(Buckets *B) {
    B->confirmed = NULL;
    B->nconf = B->ac_conf = 0;
    B->delayed = NULL;
    B->ndel = B->ac_del = 0;
    B->canceled = NULL;
    B->ncanc = B->ac_canc = 0;
}

void buckets_push(Appointment ***arr, size_t *n, size_t *ac, Appointment *a) {
    if (*n == *ac) {
        *ac = (*ac ? *ac * 2 : 8);
        *arr = (Appointment **)realloc(*arr, (*ac) * sizeof(Appointment *));
    }
    (*arr)[(*n)++] = a;
}

static int overlaps(const Appointment* a, const Appointment* b){
    return !(cmp_datetime(&a->fim,&b->ini) <= 0 || cmp_datetime(&b->fim,&a->ini) <= 0);
}

int wins_over(const Appointment *a, const Appointment *b) {
    int pa = appt_priority(a), pb = appt_priority(b);
    if (pa != pb) return (pa > pb);
    int c = cmp_datetime(&a->ini, &b->ini);
    if (c != 0) return (c < 0);
    int ra = tipo_rank_for_tiebreak(a->tipo), rb = tipo_rank_for_tiebreak(b->tipo);
    if (ra != rb) return (ra > rb);
    int d = strcmp(a->descricao, b->descricao);
    if (d != 0) return (d < 0);
    return (a->id < b->id);
}

void apply_filter(Appointment **A, int N, Buckets *B) {
    fprintf(stderr, "[debug] apply_filter: N=%d\n", N);
    if (!A || N <= 0) {
        fprintf(stderr, "[debug] apply_filter: nada a fazer\n");
        return;
    }
    
    msort((void **)A, N, cmp_by_datetime_asc, NULL);
    
    for (int z = 0; z < N; ++z) dbg_print("ord", A[z]);
    
    int i = 0;
    while (i < N) {
        int j = i;
        
        while (j + 1 < N) {
            int touch_any = 0;
            for (int k = i; k <= j; k++) {
                if (overlaps(A[k], A[j + 1])) {
                    touch_any = 1;
                    break;
                }
            }
            if (!touch_any) break;
            j++;
        }
        
        fprintf(stderr, "[grp] i=%d..j=%d\n", i, j);
        for (int k = i; k <= j; k++) dbg_print(" in", A[k]);
        
        if (i == j) {
            buckets_push(&B->confirmed, &B->nconf, &B->ac_conf, A[i]);
            dbg_print("conf", A[i]);
            i = j + 1;
            continue;
        }
        
        int gsz = j - i + 1;
        unsigned char st[256];
        for (int t = 0; t < gsz; ++t) st[t] = 0;
        
        while (1) {
            int w = -1;
            for (int t = 0; t < gsz; ++t) {
                if (st[t] == 0) {
                    if (w == -1) w = t;
                    else if (wins_over(A[i + t], A[i + w])) w = t;
                }
            }
            if (w == -1) break;
            
            buckets_push(&B->confirmed, &B->nconf, &B->ac_conf, A[i + w]);
            st[w] = 1;
            dbg_print("win", A[i + w]);
            dbg_print("conf", A[i + w]);
            
            for (int t = 0; t < gsz; ++t) {
                if (t == w || st[t] != 0) continue;
                if (overlaps(A[i + t], A[i + w])) {
                    Appointment *loser = A[i + t];
                    loser->forced_by = A[i + w]->id;
                    dbg_print("lost", loser);
                    if (appt_is_adiavel(loser)) {
                        buckets_push(&B->delayed, &B->ndel, &B->ac_del, loser);
                        st[t] = 2;
                    } else {
                        buckets_push(&B->canceled, &B->ncanc, &B->ac_canc, loser);
                        st[t] = 3;
                    }
                }
            }
        }
        
        i = j + 1;
    }
    
    fprintf(stderr, "[debug] apply_filter OK\n");
}