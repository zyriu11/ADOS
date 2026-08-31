GCC := i686-elf-gcc
ASM := i686-elf-as
SRC := $(shell find src -name "*.c")
OBJ := $(SRC:.c=.o)
CFLAGS := -std=gnu99 -ffreestanding -O2 -w
kernel: $(OBJ)
	$(ASM) src/boot.s -o src/boot.o
	$(GCC) -T src/linker.ld -o isofiles/boot/ados -ffreestanding -O2 -nostdlib src/boot.o $(OBJ) -lgcc
	xorriso -as mkisofs -b limine-bios-cd.bin -no-emul-boot -boot-load-size 4 -boot-info-table -o boot.iso isofiles

%.o: %.c
	$(GCC) -c $< -o $@ $(CFLAGS)

test:
	qemu-system-i386 -cdrom boot.iso -hda disk.img -m 4 -boot d

clean:
	find src -name "*.o" -delete
