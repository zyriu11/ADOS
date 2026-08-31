#include "../../libc/libc.h"
int read_blocknum(uint8_t *data, uint32_t blocknum) {
	uint16_t *buf = (uint16_t *)data;
	while (inb(0x1F7) & 0x80);
	outb(0x1F6, 0xE0 | ((blocknum >> 24) & 0x0F));
	inb(0x3F6); inb(0x3F6); inb(0x3F6); inb(0x3F6);	 /* Wait 400ns */
	outb(0x1F2, 1);
	outb(0x1F3, blocknum & 0xFF);
	outb(0x1F4, (blocknum >> 8) & 0xFF);
	outb(0x1F5, (blocknum >> 16) & 0xFF);
	outb(0x1F7, 0x20);
	uint8_t status;
	while ((status = inb(0x1F7)) & 0x80);
	if (status & 0x01) {
	    panic("ATA ERROR");
	}
	while (!((status = inb(0x1F7)) & 0x08)) {
   		if (status & 0x01) {
       		panic("ATA ERROR (during DRQ)\n");
   		}
   	}
   	for(size_t i = 0; i < 256; i++) {
		buf[i] = inw(0x1F0);
	}
	return 0;
}
bool ataisdrive() {
	outb(0x1F6, 0xA0);
	outb(0x1F2, 0x00);
	outb(0x1F3, 0x00);
	outb(0x1F4, 0x00);
	outb(0x1F5, 0x00);
	if(inb(0x1F7)) return true;
	return false;
}

int write_blocknum(uint8_t *data, uint32_t blocknum) {
	while (inb(0x1F7) & 0x80);
	outb(0x1F6, 0xE0 | ((blocknum >> 24) & 0x0F));
	inb(0x3F6); inb(0x3F6); inb(0x3F6); inb(0x3F6);	 /* Wait 400ns */
	outb(0x1F2, 1);
	outb(0x1F3, blocknum & 0xFF);
	outb(0x1F4, (blocknum >> 8) & 0xFF);
	outb(0x1F5, (blocknum >> 16) & 0xFF);
	outb(0x1F7, 0x30);
	uint8_t status;
	while ((status = inb(0x1F7)) & 0x80);
	if (status & 0x01) {
	    panic("ATA ERROR\n");
	}
	while (!((status = inb(0x1F7)) & 0x08)) {
   		if (status & 0x01) {
       		panic("ATA ERROR (during DRQ)\n");
   		}
   	}
   	uint16_t *buffer = (uint16_t *)data;
   	uint16_t count = 256;
	asm volatile (
    	"rep outsw"
    	: "+S"(data), "+c"(count)
    	: "d"(0x1F0)
    	: "memory"
	);
	inb(0x3F6); inb(0x3F6); inb(0x3F6); inb(0x3F6);
	outb(0x1F7, 0xE7);
	while ((status = inb(0x1F7)) & 0x80);
	if (status & 0x01) panic("Flush failed");
	return 0;
}
