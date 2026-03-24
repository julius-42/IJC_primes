/*
errors.c
Autor: Julius Kundrat FIT
Prelozene: gcc 13.3
*/

#include <stdio.h>
#include <stdlib.h>
#include "errors.h"

// Prints a warning message using fmt format
void warning(const char* fmt, ...){
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
}

// Prints a error message using fmt format and exits the program
void error_exit(const char* fmt, ...){
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    exit(1);
}