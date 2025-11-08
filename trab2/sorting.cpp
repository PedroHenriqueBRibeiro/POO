#include "sorting.h"
#include <cstdlib>

static void merge(void** a, void** t, int l, int m, int r, CmpFn cmp, void* ctx) {
    int i = l, j = m + 1, k = l;
    while (i <= m && j <= r) {
        if (cmp(a[i], a[j], ctx) <= 0) t[k++] = a[i++];
        else t[k++] = a[j++];
    }
    while (i <= m) {
        t[k++] = a[i++];
    }
    while (j <= r) {
        t[k++] = a[j++];
    }
    for (i = l; i <= r; ++i) {
        a[i] = t[i];
    }
}

static void msort_rec(void** a, void** t, int l, int r, CmpFn cmp, void* ctx) {
    if (l >= r) return;
    int m = (l + r) / 2;
    msort_rec(a, t, l, m, cmp, ctx);
    msort_rec(a, t, m + 1, r, cmp, ctx);
    merge(a, t, l, m, r, cmp, ctx);
}

void msort(void** a, int n, CmpFn cmp, void* ctx) {
    if (n <= 1) return;
    void** t = (void**)std::malloc(sizeof(void*) * n);
    msort_rec(a, t, 0, n - 1, cmp, ctx);
    std::free(t);
}