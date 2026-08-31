#include "libc.h"
size_t itoa(int value, char *buf, size_t max, int base) {
    char tmp[32];
    size_t i = 0;
    int is_negative = 0;

    if (value == 0) {
        tmp[i++] = '0';
    } else {
        if (base == 10 && value < 0) {
            is_negative = 1;
            value = -value;
        }
        while (value > 0) {
            int rem = value % base;
            tmp[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
            value /= base;
        }
        if (is_negative) tmp[i++] = '-';
    }

    size_t written = 0;
    while (i > 0 && written < max - 1) {
        buf[written++] = tmp[--i];
    }
    return written;
}