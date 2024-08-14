#ifndef WRITE_H
#define WRITE_H

#include <stdbool.h>
#include <stdio.h>
#include <analysis.h>

/**
 * 
 */
bool write_month(FILE *fd, int year, int month, MonthStatistics_t ms);

/**
 * 
 */
bool write_year(FILE *fd, YearStatistics_t ys); 

#endif