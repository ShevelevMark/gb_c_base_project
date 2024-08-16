#include <analysis.h>
#include <stdbool.h>
#include <stdio.h>

/**
 * Функция печатает в поток заголовок для информации по месяцам.
 * 
 * @param {FILE *} stream - поток для записи
 * 
 * @return {bool} - true, если операции записи прошли успешно, иначе - false 
 */
bool write_head(FILE *stream) {
    if (0 > fprintf(stream, "Year Month NuValue ErValue MonthAvg MonthMax MonthMin\n")) return false;
    return true;
}

/**
 * Функция печатает в поток данные по одному месяцу одного года.

 * @param {FILE *} stream        - поток для записи
 * @param {int} year             - год, четырёхзначное натуральное число
 * @param {int} month            - номер месяца, целое число от 1 до 12
 * @param {MonthStatistics_t} ms - копия структруры статистических данных о месяце
 * 
 * @return {bool} - true, если операции записи прошли успешно, иначе - false 
 */
bool write_month(FILE *stream, int year, int month, MonthStatistics_t ms) {
    if (ms.no_data) {
        if (0 > fprintf(stream, "%4d %5d     N/A     N/A      N/A      N/A      N/A\n", year, month)) return false;
    } else {
        if (0 > fprintf(stream, "%4d %5d %7u %7u %8d %8d %8d\n", year, month, ms.unavlbl_cnt, ms.err_cnt, ms.avg, ms.max, ms.min)) return false;
    }
    return true;
}

/**
 * Функция записи в поток статистических данных за весь год, но не отдельных месяцев.
 * 
 * @param {FILE *} stream       - поток для записи
 * @param {YearStatistics_t ys} - копия структуры статистических данных за год
 * 
 * @return {bool} - true, если операции записи прошли успешно, иначе - false 
 */
bool write_year(FILE *stream, YearStatistics_t ys) {
    /* Статистика за весь год */
    if (0 > fprintf(stream, "\nYear statictics:\n")) return false;
    if (0 > fprintf(stream, "Year NuValue ErValue YrAvg YrMax YrMin\n")) return false;
    if (0 > fprintf(stream, "%4d %7u %7u %5d %5d %5d\n", ys.year, ys.unavlbl_ctn, ys.err_cnt, ys.avg, ys.max, ys.min)) return false;
    return true;
}
/**
 * Функция печатает данные за весь год с общим заголовком:
 *     общий заголовок;
 *     данные за каждый месяц на отдельной строке;
 *     заголовок и данные за весь год.
 * 
 * @return {bool} - true, если операции записи прошли успешно, иначе - false 
 */
bool write_all(FILE *stream, YearStatistics_t ys) {
    /* Заголовок */
    if (!write_head(stream)) return false;

    /* Для каждого отдельного месяца */
    for (int m = 0; m != 12; ++m)
        if (!write_month(stream, ys.year, m + 1, ys.month[m])) return false;

    /* Статистика за весь год */
    if (!write_year(stream, ys)) return false;

    return true;
}