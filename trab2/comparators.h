#ifndef COMPARATORS_H
#define COMPARATORS_H

#include "appointments.h"

int cmp_by_datetime_asc(const void* A, const void* B, void*);
int cmp_by_id_asc(const void* A, const void* B, void*);
int cmp_by_priority_desc(const void* A, const void* B, void*);
int cmp_by_duration_asc(const void* A, const void* B, void*);
int cmp_datetime(const DateTime* a, const DateTime* b);

#endif