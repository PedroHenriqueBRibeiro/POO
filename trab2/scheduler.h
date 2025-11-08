#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "appointments.h"

struct Buckets {
    Appointment** confirmed = nullptr; size_t nconf = 0, cap_conf = 0;
    Appointment** delayed = nullptr; size_t ndel = 0, cap_del = 0;
    Appointment** canceled = nullptr; size_t ncanc = 0, cap_canc = 0;
};

bool overlaps(const Appointment* a, const Appointment* b);
bool wins_over(const Appointment* a, const Appointment* b);
void apply_filter(Appointment** A, int N, Buckets* B);

#endif