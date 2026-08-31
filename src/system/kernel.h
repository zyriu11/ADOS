#include "../libc/libc.h"
enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};
void panic(char *msg) {
	puts("KERNEL PANIC!!! ");
	puts(msg);
	puts("\nRefer to the source code for more information,\nor ask us on the discord server: tklab.eu1.netbird.services/ados/\n");
	puts("Version: ");
	puts(KERNEL_VERSION);
	while(1) {}
}
size_t cmos_mem() {
	char lomem, himem;
	outb(0x70, 0x30);
	lomem = inb(0x71);
	outb(0x70, 0x31);
	himem = inb(0x71);
	return (size_t)lomem | ((size_t)himem << 8);
}
char *map;
void init_paging() {
	map = (char *)0x20000000;
	for(size_t i = 0; i < cmos_mem() / 4; i++) {	/* Clear the memory the page sits in */
		map[i] = 0;
	}
	return;
}
size_t alloc_page() {
	for(size_t i = 0; i < cmos_mem() / 4; i++) {
		for(size_t b = 0; b < 8; b++) {		/* Find a free block */
			if(!((map[i] >> b) & 0x01)) {
				map[i] |= (1 << b);
				return (i * 8 + b) * 4096;
			}
		}
	}
	return 2147483647;
}
void free_page(void *ptr) {
	size_t page = (size_t)ptr / 4096;
	size_t i = page / 8;
	size_t b = page % 8;
	map[i] &= ~(1 << b);
	return;
}
bool ata_drive = false;
void kernelinit() {
	clear(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
	puts(" Cleared the screen\n");
	puts("Initializing PICs...\n");
	init_pics(0x20, 0x28);
	puts("Detecting master hard drive...\n");
	bool ata_drive = false;
	if(ataisdrive()) {
		puts("ATA drive detected in PIO mode!\n");
		ata_drive = true;
	} else {
		puts("No ATA drive detected! Make sure it's a compatible ATA LBA hard drive\n");
	}
	puts("Welcome to ADOS!\n\n");
}


