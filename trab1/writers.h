#ifndef WRITERS_H
#define WRITERS_H

#include "appointment.h"

void write_confirmed(const char *path, Appointment **A, int N);
void write_delayed(const char *path, Appointment **A, int N);
void write_canceled(const char *path, Appointment **A, int N);
void write_all(const char *path, Appointment **A, int N);

#endif