#include "datetime.h"
#include <cstdio>
#include <cstdlib>

int days_in_month(int y, int m) {
    static const int md[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    int r = md[m - 1];
    int leap = ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0);
    if (m == 2 && leap) r = 29;
    return r;
}

DateTime parse_date(const char* s) {
    DateTime t{};
    if (std::sscanf(s, "%d/%d/%d", &t.d, &t.m, &t.y) != 3) {
        std::fprintf(stderr, "Data inválida: %s\n", s);
        std::exit(1);
    }
    return t;
}

void parse_time_into(DateTime* t, const char* s) {
    if (std::sscanf(s, "%d:%d", &t->h, &t->min) != 2) {
        std::fprintf(stderr, "Hora inválida: %s\n", s);
        std::exit(1);
    }
}

void add_minutes(DateTime* t, int minutes) {
    t->min += minutes;
    t->h += t->min / 60;
    t->min %= 60;
    t->d += t->h / 24;
    t->h %= 24;
    while (true) {
        int dim = days_in_month(t->y, t->m);
        if (t->d <= dim) break;
        t->d -= dim;
        t->m++;
        if (t->m > 12) { t->m = 1; t->y++; }
    }
}

void add_days(DateTime* t, int days) { 
    add_minutes(t, days * 24 * 60); 
}

int cmp_datetime(const DateTime* a, const DateTime* b) {
    if (a->y != b->y) return (a->y < b->y) ? -1 : 1;
    if (a->m != b->m) return (a->m < b->m) ? -1 : 1;
    if (a->d != b->d) return (a->d < b->d) ? -1 : 1;
    if (a->h != b->h) return (a->h < b->h) ? -1 : 1;
    if (a->min != b->min) return (a->min < b->min) ? -1 : 1;
    return 0;
}

void fmt_date(const DateTime* t, char* out) { 
    std::sprintf(out, "%02d/%02d/%04d", t->d, t->m, t->y); 
}

void fmt_time(const DateTime* t, char* out) { 
    std::sprintf(out, "%02d:%02d", t->h, t->min); 
}