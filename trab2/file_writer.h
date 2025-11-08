#ifndef FILE_WRITER_H
#define FILE_WRITER_H

#include "appointments.h"
#include "scheduler.h"

void pad_id(int id, char* out);
void write_confirmed(const char* path, Appointment** A, int N);
void write_delayed(const char* path, Appointment** A, int N);
void write_canceled(const char* path, Appointment** A, int N);
void write_all(const char* path, Appointment** A, int N);

#endif