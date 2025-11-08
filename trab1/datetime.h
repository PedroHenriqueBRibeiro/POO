#ifndef DATETIME_H
#define DATETIME_H

typedef struct { int y, m, d, h, min; } DateTime;

int days_in_month(int y, int m);
DateTime parse_date(const char *s);
void parse_time_into(DateTime *t, const char *s);
void add_minutes(DateTime *t, int minutes);
void add_days(DateTime *t, int days);
int cmp_datetime(const DateTime *a, const DateTime *b);
void fmt_date(const DateTime *t, char *out);
void fmt_time(const DateTime *t, char *out);
void dbg_dt(const DateTime *t, char *o);

#endif