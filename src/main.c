#include <stdio.h>
#include <analysis.h>
#include <write.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

/**
 * Функция для печати короткой справки по ключам.
 */
static inline void print_help(void) {
    printf("Statistic application expects command line options:\n");
    printf("    -h prints help message\n");
    printf("    -f <filename> required (only once), name of a file to read data from\n");
    printf("    -m <dd> optional (only once), number of a month to print statistics\n");
}

int main(int argc, char **argv) {
    /**
     * Переменные для основных данных.
     * Объявлены заранее, чтобы не перескочить оператором goto через определения.
     */
    char *filename = NULL;
    FILE *stream = NULL;
    int month_num = 0;
    bool help_opt_set = false, filename_opt_set = false, month_opt_set = false;

    /**
     * В блоке ниже при ошибочных данных (два одинаковых флага) управление переходит в блок 
     * с отметкой END, где при необходимости происходит освобождение памяти под строку filename
     */
    { 
        int opt_code = -1;
        while (-1 != (opt_code = getopt(argc, argv, "hf:m:"))) {
            switch(opt_code) {
                case 'h':
                    help_opt_set = true;
                    goto END; /* как только встречен флаг -h мы сразу переходим в конец программы вне зависимости от других флагов */
                case 'f':
                    if (filename_opt_set) {
                        printf("-f option can not be set multiple times\nApplication terminated\n");
                        help_opt_set = true;
                        goto END; 
                    }
                    filename = malloc(strlen(optarg) + 1);
                    if (NULL == filename) {
                        printf("Internal error\nApplication terminated\n");
#ifdef _DEBUG
                        fprintf(stderr, "Can't allocate memory to store filename string\n");
#endif
                        goto END; 
                    }
                    strcpy(filename, optarg);
                    filename_opt_set = true;
                    break;
                case 'm':
                    if (month_opt_set) {
                        printf("-m option can not be set multiple times\nApplication terminated\n");
                        help_opt_set = true;
                        goto END;
                    }
                    if (1 != sscanf(optarg, "%d", &month_num) || 1 > month_num || 12 < month_num) {
                        printf("Month should be the number between 1 and 12\nApplication terminated\n");
#ifdef _DEBUG
                        fprintf(stderr, "DEBUG: error in month option {%s}\n", optarg);
#endif
                        help_opt_set = true;
                        goto END;
                    }
                    month_opt_set = true;
                    break;
            }
            /**
             * Все неизвестные флаги игнорируются, ошибки записывает сама функция getopt в поток stderr
             */
        }
    }

    if (!filename_opt_set) {
        printf("Filename is not specified\nApplication terminated\n");
        help_opt_set = true;
        goto END;
    }

    /**
     * В этом блоке мы так же при каждой ошибке уходим в блок с меткой END.
     */
    {
        /**
         * Здесь мы пытаемся открыть поток для чтения данных
         */
        stream = fopen(filename, "r");
        if (NULL == stream) {
            printf("Can't open file {%s}\nApplication terminated\n", filename);
            goto END;
        }

        YearStatistics_t ys = analysis(stream);
        fclose(stream);
        stream = NULL;
        /**
         * После чтения сразу закрываем и выставляем указатель в NULL,
         * чтобы он не остался "висячим".
         */

        if (ys.no_data) {
            printf("No data in a file {%s}\nApplication terminated\n", filename);
            goto END;
        }

        bool write_success = false;
        if (month_opt_set) {
            write_success = 
                write_head(stdout)
                && 
                write_month(stdout, ys.year, month_num, ys.month[month_num - 1])
                &&
                write_year(stdout, ys);
        } else {
            write_success = write_all(stdout, ys);
        }
#ifdef _DEBUG
        fprintf(stderr, "FORMAT WRITE %s\n", write_success ? "SUCCESS" : "FAIL");
#endif
    }

END: {
    if (NULL != filename) free(filename);
    if (help_opt_set) print_help();
}
    return 0;
}