#ifndef SORTING_H
#define SORTING_H

typedef int (*CmpFn)(const void*, const void*, void*);

void msort(void** a, int n, CmpFn cmp, void* ctx);

#endif