#include "libc.h"
bool strcmp(char *str1, char *str2) {		/* False - not equal, True - equal */
	if(strlen(str1) != strlen(str2)) return false;
	size_t i = 0;
	while(i < strlen(str1)) {
		if(str1[i] != str2[i]) return false;
		i++;
	}
	return true;
}