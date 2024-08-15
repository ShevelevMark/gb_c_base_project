#include <stdio.h>
#include <analysis.h>
#include <write.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

static void print_help(void) {
    printf("Statistic application expects command line options:\n");
    printf("    -h prints this message\n    -f <filename> required, name of a file to read data from\n    -m <dd> optional, number of a month to print statistics of\n");
}

int main(int argc, char **argv) {
#ifdef _DEBUG
    printf("DEBUG BUILD!\n"); 
#else
    printf("RELEASE BUILD!\n");
#endif

    char *filename = NULL;
    FILE *stream = NULL;
    bool need_print_help = false;
    { 
        int opt_code = -1;
        while (-1 != (opt_code = getopt(argc, argv, "hf:m:"))) {
            switch(opt_code) {
                case 'h':
                    need_print_help = true;
                    goto END; 
                case 'f':
                    if (NULL != filename) {
                        printf("This option can not be used multiple times!\nApplication terminated!\n");
                        goto END; 
                    }
                    filename = malloc(strlen(optarg) + 1);
                    if (NULL == filename) {
                        printf("Internal error!\nApplication terminated!\n");
#ifdef _DEBUG
                        fprintf(stderr, "Can't allocate memory to store filename string\n");
#endif
                        goto END; 
                    }
                    strcpy(filename, optarg);
                    break;
                case 'm':
                    printf("month: %s\n", optarg);
                    break;
            }
        }
    }

    if (NULL == filename) {
        printf("Filename is not specified!\nApplication terminated!\n");
        goto END;
    }

    {
        stream = fopen(filename, "r");
        if (NULL == stream) {
            printf("Can't open file %s.\nApplication terminated.\n", filename);
            goto END;
        }

        YearStatistics_t ys = analysis(stream);
#ifdef _DEBUG
        bool write_success = write_year(stdout, ys);
        fprintf(stderr, "FORMAT WRITE %s\n", write_success ? "SUCCESS" : "FAIL");
#else
        write_year(stdout, ys);
#endif
    }

END: {
    if (NULL != filename) free(filename);
    if (NULL != stream) fclose(stream);
    if (need_print_help) print_help();
}
    return 0;
}