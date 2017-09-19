# Compiles the bootloader

# Don't show commands
.SILENT:

# Assembler
ASM=nasm
ASM_OPTS=-f bin
ASM_OUTPUT=-o

# The files to be compiled/assembled
TARGETS=bin bin/boot.bin bin/disk.img

# Rules
all: $(TARGETS)

bin:
	echo "Creating binaries directory"
	mkdir bin/

bin/boot.bin : Bootloader/boot.asm
	echo "Assembling $@"
	$(ASM) $(ASM_OPTS) $(ASM_OUTPUT) $@ $<

bin/disk.img : bin/boot.bin
	echo "Creating a floppy image: bin/disk.img"
	dd if=/dev/zero of=$@ bs=1024 count=1440
	dd if=$< of=$@ seek=0 count=1 conv=notrunc

# Utilities
build:
	clean all

clean:
	rm -rf $(TARGETS)
