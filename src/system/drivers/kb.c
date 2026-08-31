#include "../../libc/libc.h"
char kmap[] = {
'\0','1','2','3','4','5','6','7','8','9','0','-','=','\b',
'\0','Q','W','E','R','T','Y','U','I','O','P','[',']','\n',			/* '\0' means not implemented */
'\0','A','S','D','F','G','H','J','K','L',';','\'','`','\0','\\',
'Z','X','C','V','B','N','M',',','.','/','\0','\0','\0',' '
};
char getch() {
	while(!(inb(0x64) & 1)) { } /* Wait for 1st bit of 0x64(the status code) to be 1 */
	char kb = inb(0x60);		/* Read character from register 0x60 */
	if(kb & 0x80) return getch();		/* Dont look at key releases */
	return kmap[kb-1];
}











