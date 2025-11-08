#include "result_calculator.h"
#include "sorting.h"
#include "comparators.h"
#include <cstdio>
#include <cstdlib>

int read_positions(const char* path, int* pi, int* pj, int* pk, int* pm) {
    std::FILE* f = std::fopen(path, "r"); if (!f) return 0;
    if (std::fscanf(f, "%d", pi) != 1) { std::fclose(f); return 0; }
    if (std::fscanf(f, "%d", pj) != 1) { std::fclose(f); return 0; }
    if (std::fscanf(f, "%d", pk) != 1) { std::fclose(f); return 0; }
    if (std::fscanf(f, "%d", pm) != 1) { std::fclose(f); return 0; }
    std::fclose(f); return 1;
}

void calculate_and_write_result(const Buckets& B, Appointment** A, size_t N, int i, int j, int k, int m) {
    Appointment** CONF = (Appointment**)std::malloc(sizeof(Appointment*) * B.nconf);
    for (size_t t = 0; t < B.nconf; ++t) {
        CONF[t] = B.confirmed[t];
    }
    msort((void**)CONF, (int)B.nconf, cmp_by_datetime_asc, nullptr);

    Appointment** DEL = (Appointment**)std::malloc(sizeof(Appointment*) * B.ndel);
    for (size_t t = 0; t < B.ndel; ++t) {
        DEL[t] = B.delayed[t];
    }
    msort((void**)DEL, (int)B.ndel, cmp_by_priority_desc, nullptr);

    Appointment** CANC = (Appointment**)std::malloc(sizeof(Appointment*) * B.ncanc);
    for (size_t t = 0; t < B.ncanc; ++t) {
        CANC[t] = B.canceled[t];
    }
    msort((void**)CANC, (int)B.ncanc, cmp_by_duration_asc, nullptr);

    Appointment** ALL = (Appointment**)std::malloc(sizeof(Appointment*) * N);
    for (size_t t = 0; t < N; ++t) {
        ALL[t] = A[t];
    }
    msort((void**)ALL, (int)N, cmp_by_id_asc, nullptr);

    int sum = 0;
    if (i >= 1 && i <= (int)B.nconf) sum += CONF[i - 1]->dur_min;
    if (j >= 1 && j <= (int)B.ndel) sum += DEL[j - 1]->dur_min;
    if (k >= 1 && k <= (int)B.ncanc) sum += CANC[k - 1]->dur_min;
    if (m >= 1 && m <= (int)N) sum += ALL[m - 1]->dur_min;
    char result_path[256];
    std::snprintf(result_path, sizeof(result_path), "resultados/resultado.txt");
    
    std::FILE* f = std::fopen(result_path, "w"); 
    if (!f) { std::perror("open"); std::exit(1); }
    std::fprintf(f, "%d", sum);
    std::fclose(f);
    
    std::free(CONF); 
    std::free(DEL); 
    std::free(CANC); 
    std::free(ALL);
}