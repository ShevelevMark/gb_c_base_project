#include <stdio.h>
#include <analysis.h>

int main(int argc, char **argv) {
#ifdef _DEBUG
    printf("DEBUG BUILD!\n"); 
#else
    printf("RELEASE BUILD!\n");
#endif
    
    YearStatistics_t ys = analysis(stdin);
    if (ys.no_data) {
        printf("No data in a file\n");
    } else {
        printf("Year %4d: {avg %2d; min %2d; max %2d; error lines %6u;}\n", ys.year, ys.avg, ys.min, ys.max, ys.err_cnt);
        for (unsigned m = 0; m != 12; ++m)
            if (ys.month[m].no_data) {
                printf("Month %2d No data\n", m + 1);
            } else {
                MonthStatistics_t ms = ys.month[m];
                printf("Month %2d: {avg %2d; min %2d; max %2d; error lines %6u;}\n", m + 1, ms.avg, ms.min, ms.max, ms.err_cnt);
            }
    }

    return 0;
}