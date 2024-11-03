#ifndef OS_H
#define OS_H
#include <stdio.h>
#include <stdlib.h>

int checkOS() {
    #ifdef _WIN32
        printf("Running on Windows\n");
        return 1;
    #elif __APPLE__
        printf("Running on macOS\n");
        return 2;
    #elif __linux__
        printf("Running on Linux\n");
        return 3;
    #else
        printf("Unknown Operating System\n");
    #endif
    return 0;
}


#endif 