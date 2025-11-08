#include "comparators.h"
#include "utils.h"
#include "datetime.h"

int cmp_by_datetime_asc(const void* A, const void* B, void*) {
    const Appointment* a = (const Appointment*)A; 
    const Appointment* b = (const Appointment*)B;
    int c = cmp_datetime(&a->ini, &b->ini);
    if (c) return c;
    if (a->id != b->id) {
        return (a->id < b->id) ? -1 : 1;
    }
    return 0;
}

int cmp_by_id_asc(const void* A, const void* B, void*) {
    const Appointment* a = (const Appointment*)A; 
    const Appointment* b = (const Appointment*)B;
    if (a->id != b->id) {
        return (a->id < b->id) ? -1 : 1;
    }
    return 0;
}

int cmp_by_priority_desc(const void* A, const void* B, void*) {
    const Appointment* a = (const Appointment*)A; 
    const Appointment* b = (const Appointment*)B;
    int pa = a->priority(), pb = b->priority(); if (pa != pb) return (pa > pb) ? -1 : 1;
    int c = cmp_datetime(&a->ini, &b->ini); if (c) return c;
    int ra = tipo_rank_for_tiebreak(a->tipo), rb = tipo_rank_for_tiebreak(b->tipo); if (ra != rb) return (ra > rb) ? -1 : 1;
    int d = std::strcmp(a->descricao.c_str(), b->descricao.c_str()); if (d != 0) return d;
    return (a->id < b->id) ? -1 : 1;
}

int cmp_by_duration_asc(const void* A, const void* B, void*) {
    const Appointment* a = (const Appointment*)A; 
    const Appointment* b = (const Appointment*)B;
    if (a->dur_min != b->dur_min) return (a->dur_min < b->dur_min) ? -1 : 1;

    char baseA[128], baseB[128];
    int ra = roman_suffix_value(a->descricao.c_str(), baseA, sizeof(baseA));
    int rb = roman_suffix_value(b->descricao.c_str(), baseB, sizeof(baseB));

    if (ra != -1 && rb != -1 && std::strcmp(baseA, baseB) == 0) {
        if (ra != rb) return (ra < rb) ? -1 : 1;
    }
    else {
        int d = std::strcmp(a->descricao.c_str(), b->descricao.c_str());
        if (d != 0) return (d > 0) ? -1 : 1; // DESC
    }
    if (a->id != b->id) {
        return (a->id < b->id) ? -1 : 1;
    }
    return 0;
}