#include "libc.h"
int snprintf(char *str, size_t size, const char *format, ...) {
    if (size == 0) return 0;
    
    va_list args;
    va_start(args, format);
    
    size_t written = 0;
    while (*format && written < size - 1) {
        if (*format == '%') {
            format++;
            if (*format == 's') {
                char *s = va_arg(args, char*);
                while (*s && written < size - 1) {
                    str[written++] = *s++;
                }
            } else if (*format == 'd') {
                int d = va_arg(args, int);
                written += itoa(d, str + written, size - written, 10);
            } else if (*format == 'x') {
                int x = va_arg(args, int);
                written += itoa(x, str + written, size - written, 16);
            }
        } else {
            str[written++] = *format;
        }
        format++;
    }
    
    str[written] = '\0';
    va_end(args);
    return written;
}