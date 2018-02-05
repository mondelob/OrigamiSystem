; kernel.asm
; 2018-01-25
; Bruno Mondelo Giaramita

format elf                       ; Specify output format ELF
use32                            ; 32 Bit code

; include "graph/vga.inc"
include "graph/term.inc"

public kernel_main               ; Set the main function accessible for the
                                 ; multiboot

section ".text"

kernel_main:
    call init_term
    sprint "H"

    ret

hellomsg db 'Hello World!', 0