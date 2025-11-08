#ifndef COMPARATORS_H
#define COMPARATORS_H

#include "appointment.h"

int cmp_by_datetime_asc(const void *A, const void *B, void *ctx);
int cmp_by_id_asc(const void *A, const void *B, void *ctx);
int cmp_by_priority_desc(const void *A, const void *B, void *ctx);
int cmp_by_duration_asc(const void *A, const void *B, void *ctx);

#endif