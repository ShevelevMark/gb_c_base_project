#include <analysis.h>
#include <stdbool.h>
#include <stdio.h>

bool write_month(FILE *fd, int year, int month, MonthStatistics_t ms) {
    if (ms.no_data) {
        if (0 > fprintf(fd, "%4d %5d     N/A     N/A      N/A      N/A      N/A\n", year, month)) return false;
    } else {
        if (0 > fprintf(fd, "%4d %5d %7u %7u %8d %8d %8d\n", year, month, ms.unavlbl_cnt, ms.err_cnt, ms.avg, ms.max, ms.min)) return false;
    }
    return true;
}

bool write_year(FILE *fd, YearStatistics_t ys) {
    /* Нет данных по году */
    if (ys.no_data) {
        if (0 > fprintf(fd, "Data not available\n")) return false;
        return true;
    }
    /* Заголовок */
    if (0 > fprintf(fd, "Year Month NuValue ErValue MonthAvg MonthMax MonthMin\n")) return false;
    /* Для каждого отдельного месяца */
    for (int m = 0; m != 12; ++m)
        if (!write_month(fd, ys.year, m + 1, ys.month[m])) return false;

    /* Статистика за весь год*/
    if (0 > fprintf(fd, "-----------------------------------------------------\n")) return false;
    if (0 > fprintf(fd, "Year NuValue ErValue YrAvg YrMax YrMin\n")) return false;
    if (0 > fprintf(fd, "%4d %7u %7u %5d %5d %5d\n", ys.year, ys.unavlbl_ctn, ys.err_cnt, ys.avg, ys.max, ys.min)) return false;
    return true;
}