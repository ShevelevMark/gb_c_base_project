#ifndef WRITE_H
#define WRITE_H

#include <stdbool.h>
#include <stdio.h>
#include <analysis.h>

/**
 * Функция печатает в поток заголовок для информации по месяцам.
 * 
 * @param {FILE *} stream - поток для записи
 * 
 * @return {bool} - true, если операции записи прошли успешно, иначе - false 
 */
bool write_head(FILE *fd);

/**
 * Функция печатает в поток данные по одному месяцу одного года.

 * @param {FILE *} stream        - поток для записи
 * @param {int} year             - год, четырёхзначное натуральное число
 * @param {int} month            - номер месяца, целое число от 1 до 12
 * @param {MonthStatistics_t} ms - копия структруры статистических данных о месяце
 * 
 * @return {bool} - true, если операции записи прошли успешно, иначе - false 
 */
bool write_month(FILE *fd, int year, int month, MonthStatistics_t ms);

/**
 * Функция записи в поток статистических данных за весь год, но не отдельных месяцев.
 * 
 * @param {FILE *} stream       - поток для записи
 * @param {YearStatistics_t ys} - копия структуры статистических данных за год
 * 
 * @return {bool} - true, если операции записи прошли успешно, иначе - false 
 */
bool write_year(FILE *fd, YearStatistics_t ys); 

/**
 * Функция печатает данные за весь год с общим заголовком:
 *     общий заголовок;
 *     данные за каждый месяц на отдельной строке;
 *     заголовок и данные за весь год.
 * 
 * @return {bool} - true, если операции записи прошли успешно, иначе - false 
 */
bool write_all(FILE *fd, YearStatistics_t ys);

#endif