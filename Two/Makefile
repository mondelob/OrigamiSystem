# Compiles the bootloader

# Don't show commands
# .SILENT:

# Assembler
ASM=nasm
ASM_OPTS=-felf32
ASM_OUTPUT=-o

# C compiler
CC=i686-elf-gcc
CC_OPTS=-std=gnu99 -ffreestanding -O2 -Wall -Wextra
CC_INPUT=-c
CC_OUTPUT=-o

# The files to be compiled/assembled
TARGETS=bin bin/boot.o bin/kernel.o bin/myos.bin

# Rules
all: $(TARGETS)

bin:
	mkdir bin/

bin/boot.o : Bootloader/boot.asm
	$(ASM) $(ASM_OPTS) $(ASM_OUTPUT) $@ $<

bin/kernel.o : Kernel/kernel.c
	$(CC) $(CC_INPUT) $< $(CC_OUTPUT) $@ $(CC_OPTS)

bin/myos.bin :
	$(CC) -T linker.ld $(CC_OUTPUT) $@ -ffreestanding -O2 -nostdlib bin/boot.o bin/kernel.o -lgcc

# Utilities
build:
	clean all

clean:
	rm -rf $(TARGETS)
