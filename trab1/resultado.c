#include "resultado.h"
#include "sort.h"
#include "comparators.h"
#include <stdlib.h>
#include <stdio.h>

int read_positions(const char *path, int *pi, int *pj, int *pk, int *pm) {
    FILE *f = fopen(path, "r");
    if (!f) return 0;
    if (fscanf(f, "%d", pi) != 1) {
        fclose(f);
        return 0;
    }
    if (fscanf(f, "%d", pj) != 1) {
        fclose(f);
        return 0;
    }
    if (fscanf(f, "%d", pk) != 1) {
        fclose(f);
        return 0;
    }
    if (fscanf(f, "%d", pm) != 1) {
        fclose(f);
        return 0;
    }
    fclose(f);
    return 1;
}

void show_pick(const Appointment *const *L, size_t n, int pos, const char *name) {
    if (pos >= 1 && (size_t)pos <= n) {
        const Appointment *a = L[(size_t)(pos - 1)];
        fprintf(stderr, "[pick] %s[%d] -> id=%06d dur=%d\n", name, pos, a->id, a->dur_min);
    }
}

void write_result_sum(const char *path,
                     Appointment **confirmed, int nconf,
                     Appointment **delayed, int ndel,
                     Appointment **canceled, int ncanc,
                     Appointment **all, int nall,
                     int i, int j, int k, int m) {
    int sum = 0;
    if (i >= 1 && i <= nconf) sum += confirmed[i - 1]->dur_min;
    if (j >= 1 && j <= ndel) sum += delayed[j - 1]->dur_min;
    if (k >= 1 && k <= ncanc) sum += canceled[k - 1]->dur_min;
    if (m >= 1 && m <= nall) sum += all[m - 1]->dur_min;
    
    FILE *f = fopen(path, "w");
    if (!f) {
        perror("open");
        exit(1);
    }
    fprintf(f, "%d", sum);
    fclose(f);
}