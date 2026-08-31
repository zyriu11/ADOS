#ifndef LIBC_H
#define LIBC_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
char atoh(char *p);
size_t atoi(char *p);
void gets(char *str, size_t limit);
size_t itoa(int value, char *buf, size_t max, int base);
void *memcpy (void *dest, const void *src, size_t len);
void *memset (void *dest, register int val, register size_t len);
int printf(const char *format, ...);
int vsnprintf(char *str, size_t size, const char *format, va_list args);
char *strchr(const char *s, int c);
bool strcmp(char *str1, char *str2);
size_t strcspn(char c, char *string);
size_t strlen(const char* str);
int strncasecmp(const char *s1, const char *s2, size_t n);
char *strncpy (char *s1, const char *s2, size_t n);
int strnlen (const char *s, size_t maxlen);
char *strrchr(const char *s, int c);
int snprintf(char *str, size_t size, const char *format, ...);


static void outb( unsigned short port, unsigned char val ) {
   asm volatile("outb %0, %1" : : "a"(val), "Nd"(port) );
}

static __inline unsigned char inb (unsigned short int port) {
  unsigned char _v;

  __asm__ __volatile__ ("inb %w1,%0":"=a" (_v):"Nd" (port));
  return _v;
}

static inline uint16_t inw(uint16_t port) {
    	uint16_t value;
   		__asm__ volatile ("inw %1, %0"
        				          : "=a"(value)
                 				  : "Nd"(port));
    	return value;
}

static void outw(uint16_t port, uint16_t value) {
   		__asm__ volatile ("outw %0, %1"
        				          : "=a"(value)
                 				  : "Nd"(port));
    	return;
}


void init_pics(int pic1, int pic2);
int read_blocknum(uint8_t *data, uint32_t blocknum);
bool ataisdrive();
int write_blocknum(uint8_t *data, uint32_t blocknum);
char getch();
void clear(char f, char b);
void update_cursor(int x, int y);
void terminal_setcolor(uint8_t color);
void putxy(char c, uint8_t color, size_t x, size_t y);
void putch(char c);
void terminal_write(const char* data, size_t size);
void puts(const char* data);
void panic(char *msg);
size_t cmos_mem();
void init_paging();
size_t alloc_page();
void free_page(void *ptr);
void kernelinit();

#endif