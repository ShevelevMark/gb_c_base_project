#include <stdbool.h>
#include <stdio.h>

struct MonthStatisticsStruct {
    bool no_data;
    int avg, max, min;
    unsigned err_cnt, unavlbl_cnt;
};

typedef struct MonthStatisticsStruct MonthStatistics_t;

struct YearStatisticsStruct {
    bool no_data;
    int year;
    int avg, max, min;
    unsigned err_cnt, unavlbl_ctn;
    MonthStatistics_t month[12];
};

typedef struct YearStatisticsStruct YearStatistics_t;

YearStatistics_t analysis(FILE *fd);