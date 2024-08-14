/**
 * Функции для работы с датой: год / месяц
 **/

#include <date.h>
#include <stdbool.h>

/**
 * Является ли год високосным (29 дней в феврале) по григорианскому календарю.
 * 
 * @param {int} year - год не менее 1900
 * 
 * @return {bool} - true, если год високосный, иначе - false
 */
bool is_leap(int year) {
    return 0 == year % 4 && 0 != year % 100 || 0 == year % 400;
}

/**
 * Функция возвращает количество дней в месяце с учётом високосного дня
 * по григорианскому календарю.
 * 
 * @param {int} year  - год, не менее 1900
 * @param {int} month - номер месяца от 1 до 12
 * 
 * @return {int} - количество дней в месяце или 0 в случае ошибки
 */
int days_in_month(int year, int month) {
    switch(month) {
        case 1: return 31;
        case 2: return is_leap(year) ? 29 : 28;
        case 3: return 31;
        case 4: return 30;
        case 5: return 31;
        case 6: return 30;
        case 7: return 31;
        case 8: return 31;
        case 9: return 30;
        case 10: return 31;
        case 11: return 30;
        case 12: return 31;
    }
    return 0;
}

/**
 * Функция вычисляет количество минут в месяце с учётом високосного дня 
 * по григорианскому календарю.
 * 
 * @param {int} year  - год, не менее 1900
 * @param {int} month - номер месяца от 1 до 12
 * 
 * @return {int} - количество минут в месяце или 0 в случае ошибки 
 */
int minutes_in_month(int year, int month) {
    return 24 * 60 * days_in_month(year, month);
}
