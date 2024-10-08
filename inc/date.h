#ifndef DATE_H
#define DATE_H

#include <stdbool.h>

/**
 * Является ли год високосным (29 дней в феврале) по григорианскому календарю.
 * 
 * @param {int} year - год не менее 1900
 * 
 * @return {bool} - true, если год високосный, иначе - false
 */
bool is_leap(int year);

/**
 * Функция возвращает количество дней в месяце с учётом високосного дня
 * по григорианскому календарю.
 * 
 * @param {int} year  - год, не менее 1900
 * @param {int} month - номер месяца от 1 до 12
 * 
 * @return {int} - количество дней в месяце или 0 в случае ошибки
 */
int days_in_month(int year, int month);

/**
 * Функция вычисляет количество минут в месяце с учётом високосного дня 
 * по григорианскому календарю.
 * 
 * @param {int} year  - год, не менее 1900
 * @param {int} month - номер месяца от 1 до 12
 * 
 * @return {int} - количество минут в месяце или 0 в случае ошибки 
 */
int minutes_in_month(int year, int month);

#endif