# Bruno Mondelo Giaramita
# mondelob14@gmail.com

.SILENT:

# C compiler
CC=gcc
CCOUTPUT=--output

# The files to compile
TARGETS=bin bin/orsh

# Rules
all: $(TARGETS)

bin:
	mkdir bin && echo "Created binaries directory: $@"

bin/orsh: src/origami_shell.c
	echo "Compiling: $@"
	$(CC) $(CCOUTPUT) $@ $< && echo "Succesfully compiled..." || echo "ERROR: compiling $@"

# Utilities
build: clean all

clean:
	rm -rf $(TARGETS)
