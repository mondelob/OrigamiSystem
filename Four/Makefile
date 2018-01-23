# Compiles the bootloader

# Don't show commands
# .SILENT:

# Assembler
ASM=fasm

# The files to be compiled/assembled
TARGETS=bin bin/boot.bin bin/disk.img

# Rules
all: $(TARGETS)

bin:
	echo "Creating binaries directory"
	mkdir bin/

bin/boot.bin : src/boot.asm
	echo "Assembling $@"
	$(ASM) $< $@

bin/disk.img : bin/boot.bin
	echo "Creating a floppy image: bin/disk.img"
	dd if=/dev/zero of=$@ bs=1024 count=1440
	dd if=$< of=$@ seek=0 count=1 conv=notrunc

# Utilities
build:
	clean all

clean:
	rm -rf $(TARGETS)
