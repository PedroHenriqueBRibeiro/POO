#ifndef RESULT_CALCULATOR_H
#define RESULT_CALCULATOR_H

#include "scheduler.h"

int read_positions(const char* path, int* pi, int* pj, int* pk, int* pm);
void calculate_and_write_result(const Buckets& B, Appointment** A, size_t N, int i, int j, int k, int m);

#endif