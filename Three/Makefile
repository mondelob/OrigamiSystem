# Compiles the bootloader

# Don't show commands
# .SILENT:

# Assembler
ASM=fasm

# C compiler
CC=i686-elf-gcc
CC_OUTPUT=-o

# The files to be compiled/assembled
# TARGETS=bin bin/boot.o bin/kernel.o bin/myos.bin
TARGETS=bin bin/multiboot.o bin/kernel.o bin/threeos.bin

# Rules
all: $(TARGETS)

bin:
	@mkdir bin/

bin/multiboot.o : Bootloader/multiboot.asm
	$(ASM) $< $@

bin/kernel.o : Kernel/main.asm
	$(ASM) $< $@

bin/threeos.bin :
	$(CC) -T linker.ld $(CC_OUTPUT) $@ -ffreestanding -O2 -nostdlib bin/multiboot.o bin/kernel.o -lgcc

# Utilities
build:
	clean all

clean:
	rm -rf $(TARGETS)
