#include <analysis.h>
#include <read.h>
#include <stdio.h>
#include <limits.h>

#ifdef _DEBUG
#include <stdio.h>
#endif

static inline int max_analysis(int a, int b) { return a > b ? a : b; }
static inline int min_analysis(int a, int b) { return a < b ? a : b; }

YearStatistics_t analysis(FILE *fd) {
    typedef struct { int year, month, day, hour, minute, temperature; } instant_t;
    
    MonthStatistics_t ms = {.no_data = true, .avg = 0, .min = INT_MAX, .max = INT_MIN, .err_cnt = 0u, .unavlbl_cnt = 0u};
    YearStatistics_t ys = {.no_data = true, .year = 0, .avg = 0, .min = INT_MAX, .max = INT_MIN, .err_cnt = 0u, .unavlbl_ctn = 0u, .month = {ms, ms, ms, ms, ms, ms, ms, ms, ms, ms, ms, ms} };

    instant_t i;
    int year_cnt = 0, month_cnt = 0;
    int curr_month = 1;

    char buf[22] = {0};
#ifdef _DEBUG
    unsigned line_cnt = 0;
#endif
    while (read_line(fd, buf)) {
#ifdef _DEBUG
        ++line_cnt;
        fprintf(stderr, "DEBUG: line %6u; buf = {%s} ", line_cnt, buf);
#endif
        if (!validate_string(buf) || !validate_data(buf, &i.year, &i.month, &i.day, &i.hour, &i.minute, &i.temperature)) {
#ifdef _DEBUG
            if (!validate_string(buf)) {
                fprintf(stderr,"validate string FAIL!\n");
            } else if (!validate_data(buf, &i.year, &i.month, &i.day, &i.hour, &i.minute, &i.temperature)) {
                fprintf(stderr,"validate data FAIL!\n");
            }
#endif
            ++ys.month[curr_month - 1].err_cnt, ++ys.err_cnt;
            continue;
        }
#ifdef _DEBUG
        fprintf(stderr,"good data: %4d %2d %2d %2d %2d %3d\n", i.year, i.month, i.day, i.hour, i.minute, i.temperature);
#endif

        if (ys.no_data) ys.year = i.year, ys.no_data = false;

        if (i.month != curr_month) {
            if (0 != month_cnt) {
                ys.month[curr_month - 1].avg /= month_cnt;
                ys.month[curr_month - 1].no_data = false;
            }
            curr_month = i.month;
            month_cnt = 0u;
        }

        ++month_cnt, ++year_cnt;
        ys.month[curr_month - 1].max = max_analysis(ys.month[curr_month - 1].max, i.temperature);
        ys.month[curr_month - 1].min = min_analysis(ys.month[curr_month - 1].min, i.temperature);
        ys.month[curr_month - 1].avg += i.temperature;

        ys.max = max_analysis(ys.max, i.temperature);
        ys.min = min_analysis(ys.min, i.temperature);
        ys.avg += i.temperature;
    }

    if (0 != month_cnt) {
        ys.month[curr_month - 1].avg /= month_cnt;
        ys.month[curr_month - 1].no_data = false;
    }

    if (0 != year_cnt) {
        ys.avg /= year_cnt;
    }

    return ys;
}