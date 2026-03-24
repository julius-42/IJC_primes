#include <stdarg.h>

#ifndef ERRORS_H
#define ERRORS_H

void warning(const char* fmt, ...);

void error_exit(const char* fmt, ...);

#endif