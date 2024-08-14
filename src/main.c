#include <stdio.h>
#include <analysis.h>

int main(int argc, char **argv) {
#ifdef _DEBUG
    printf("DEBUG BUILD!\n"); 
#else
    printf("RELEASE BUILD!\n");
#endif
    return 0;
}