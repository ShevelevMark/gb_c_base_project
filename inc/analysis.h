#include <stdbool.h>
#include <stdio.h>

/**
 * Структура для сохранения статистических данных за месяц.
 */
struct MonthStatisticsStruct {
    bool no_data;
    int avg, max, min;
    unsigned err_cnt, unavlbl_cnt;
};

typedef struct MonthStatisticsStruct MonthStatistics_t;

/**
 * Структура для сохранения статистических данных за весь год.
 */
struct YearStatisticsStruct {
    bool no_data;
    int year;
    int avg, max, min;
    unsigned err_cnt, unavlbl_ctn;
    MonthStatistics_t month[12];
};

typedef struct YearStatisticsStruct YearStatistics_t;

/**
 * Функция статистического анализа данных из потока.
 * Читает данные, пропуская некорректные, вычисляет максимальную, минимальную и среднюю температуры для 
 * каждого месяца и для всего года в целом. 
 * Среднее вычисляется прямой суммой прочитанных температур и делением на количество успешных измерений,
 * без интерполяции.
 * 
 * @param {FILE *} fd - указатель на поток символных данных
 * 
 * @return {YearStatistics_t} - статистика за год
 */
YearStatistics_t analysis(FILE *fd);