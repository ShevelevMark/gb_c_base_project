#include <stdio.h>
#include <analysis.h>
#include <write.h>

int main(int argc, char **argv) {
#ifdef _DEBUG
    printf("DEBUG BUILD!\n"); 
#else
    printf("RELEASE BUILD!\n");
#endif
    YearStatistics_t ys = analysis(stdin);
#ifdef _DEBUG
    bool write_success = write_year(stdout, ys);
    fprintf(stderr, "FORMAT WRITE %s\n", write_success ? "SUCCESS" : "FAIL");
#else
    write_year(stdout, ys);
#endif

    return 0;
}