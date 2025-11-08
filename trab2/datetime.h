#ifndef DATETIME_H
#define DATETIME_H

struct DateTime { 
    int y = 0, m = 0, d = 0, h = 0, min = 0; 
};

int days_in_month(int y, int m);
DateTime parse_date(const char* s);
void parse_time_into(DateTime* t, const char* s);
void add_minutes(DateTime* t, int minutes);
void add_days(DateTime* t, int days);
int cmp_datetime(const DateTime* a, const DateTime* b);
void fmt_date(const DateTime* t, char* out);
void fmt_time(const DateTime* t, char* out);

#endif