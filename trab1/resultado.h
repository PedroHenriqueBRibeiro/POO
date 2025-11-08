#ifndef RESULTADO_H
#define RESULTADO_H

#include "appointment.h"

int read_positions(const char *path, int *pi, int *pj, int *pk, int *pm);
void show_pick(const Appointment *const *L, size_t n, int pos, const char *name);
void write_result_sum(const char *path,
                     Appointment **confirmed, int nconf,
                     Appointment **delayed, int ndel,
                     Appointment **canceled, int ncanc,
                     Appointment **all, int nall,
                     int i, int j, int k, int m);

#endif