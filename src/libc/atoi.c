#include "libc.h"

size_t atoi(char *p) {
    size_t k = 0;
    while (*p) {
        k = (k << 3) + (k << 1) + (*p) - '0';
        p++;
     }
     return k;
}