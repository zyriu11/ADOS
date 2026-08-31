#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>
#define KERNEL_VERSION "b1.0"

#include "system/kernel.h"
#include "system/fat32/fat32.h"
#include "system/fat32/fatinternal.h"

#define NO_ERROR 0
#define FILE_OPEN_ERROR -1
#define DATA_READ_ERROR -2
#define DATA_WRITE_ERROR -3
#define DATA_MISMATCH_ERROR -4
#define FAT32_DIR_ENTRY_SIZE  32
#define ATTR_DIRECTORY        0x10
#define ATTR_LONG_NAME        0x0F
void kernel_main(void) {
	kernelinit();
	TFFile *fp;
    	char data;
    	int rc;
    	if(tf_init()) panic("dupa");
    	TFFile *dir_stream = NULL;
	char buffer[512];
	char write[1024];
	while(1) {
		char cmd[512];
		putch('>');
		gets(cmd, 512);
		char argv[8][64];
        	for(size_t i = 0; i < 8; i++) {
            		for(size_t j = 0; j < 64; j++) {
                		argv[i][j] = 0;
            		}
       		}

		size_t i = 0;
		size_t argc = 0;
		size_t l = 0;
		 while(cmd[i] != '\n' && cmd[i] != '\0') {
            		if(cmd[i] == ' ') {
                		argv[argc][l] = '\0';
                		l = 0;
                		argc++;
                		i++;
                		continue;
            		}
            		argv[argc][l++] = cmd[i++];
        		}
        		argv[argc][l] = '\0';

        	if (argv[0][0] == '\0') continue;

		if(strcmp(argv[0], "LS")) {
    				FatFileEntry entry;
  				int result;
				while (1) {
     						result = tf_listdir("/", &entry, &dir_stream);
       						if (result == 1) {
       							if (entry.msdos.attributes == 0x0F) {
         							continue; 
      							}
        					if (entry.msdos.attributes & 0x10) {
        						puts("DIR: ");
            						for(int i = 0; i < 8; i++) {
            							putch(entry.msdos.filename[i]);
            						}
            						putch('\n');
        					}
        					else {
            						if (entry.msdos.extension[0] != ' ') {
            							puts("FILE: ");
                						for(int i = 0; i < 8; i++) {
            								putch(entry.msdos.filename[i]);
            							}
            							putch('\n');
            						}
            					else {
            						puts("FILE: ");
                					for(int i = 0; i < 8; i++) {
            							putch(entry.msdos.filename[i]);
            						}
            						for(int i = 0; i < 3; i++) {
            							putch(entry.msdos.extension[i]);
            						}
            						putch('\n');
            					}
        					}
        					}
        						else if (result == 0 && dir_stream == NULL) {
            							break;
        						}
        			continue;
        	}
        	}
       		else if(strcmp(argv[0], "PANIC")) {
			panic("This is a user-triggered kernel panic, reboot your computer.");
		}
		
		
		else if(strcmp(argv[0], "HELP")) {
			puts("List of available commands:\nREAD, ASCWRITE, HEXWRITE, PANIC, HELP, ZERO, RUN\n");
			continue;
		}
		
		
		else {
			puts(argv[0]);
			puts(": Command not found\n");
		}
	}
}
