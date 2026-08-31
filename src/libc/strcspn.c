#include "libc.h"
size_t strcspn(char c, char *string) {
	for(size_t i = 0; i < strlen(string); i++) {
		if(c==string[i]) return i;
	}
	return 2147483647;
}