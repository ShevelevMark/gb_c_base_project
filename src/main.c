#include <stdio.h>

int main(int argc, char **argv) {
#ifdef _DEBUG
    printf("New project, DEBUG BUILD!");
#else
    printf("New project, RELEASE BUILD!");
#endif
    return 0;
}