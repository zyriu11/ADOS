#include "libc.h"
void gets(char *str, size_t limit) {
	size_t index = 0;
	char i = 0;
	loop:
		i = getch();
		if(i == '\n') goto end;
		if(i == '\b') {
			if(index > 0) {
				str[index--] = ' ';
				putch('\b');
				putch(' ');
				putch('\b');
			}
			goto loop;
		}
		if(index != limit) {
			str[index++] = i;
			putch(i);
		}
	goto loop;
	end:
	str[index++] = '\n';
	str[index] = '\0';
	putch('\n');
	return;
}