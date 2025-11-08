#ifndef SORT_H
#define SORT_H

#include <stddef.h>

typedef int (*CmpFn)(const void *, const void *, void *);

void msort(void **a, int n, CmpFn cmp, void *ctx);

#endif