#include "libc.h"
int printf(const char *format, ...) {
    char buf[256];
    va_list args;
    va_start(args, format);
    int len = snprintf(buf, sizeof(buf), format, args);
    va_end(args);
    puts(buf);
    return len;
}