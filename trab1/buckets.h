#ifndef BUCKETS_H
#define BUCKETS_H

#include "appointment.h"
#include "sort.h"

typedef struct {
    Appointment **confirmed;
    size_t nconf, ac_conf;
    Appointment **delayed;
    size_t ndel, ac_del;
    Appointment **canceled;
    size_t ncanc, ac_canc;
} Buckets;

void buckets_init(Buckets *B);
void buckets_push(Appointment ***arr, size_t *n, size_t *ac, Appointment *a);
int wins_over(const Appointment *a, const Appointment *b);
void apply_filter(Appointment **A, int N, Buckets *B);

#endif