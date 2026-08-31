#include "libc.h"
int strncasecmp(const char *s1, const char *s2, size_t n) {
    if (n == 0) return 0;
    while (n-- > 0) {
        unsigned char c1 = *s1++;
        unsigned char c2 = *s2++;
        if (c1 >= 'A' && c1 <= 'Z') c1 += 32;
        if (c2 >= 'A' && c2 <= 'Z') c2 += 32;
        
        if (c1 != c2 || c1 == '\0') {
            return c1 - c2;
        }
    }
    return 0;
}