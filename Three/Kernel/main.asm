; kernel.asm
; 2018-01-25
; Bruno Mondelo Giaramita

format elf                       ; Specify output format ELF
use32                            ; 32 Bit code

include "graph/vga.inc"

public kernel_main               ; Set the main function accessible for the
                                 ; multiboot

section ".text"

kernel_main:

    mov bh, VGA_LIGHT_BLUE       ; Set BH register to the foreground color
    mov bl, VGA_MAGENTA          ; Set BL register to the background color
    call vga_color

    mov bh, ah

    mov bl, "H"
    putchar bx, 0, 0

    mov bl, "e"
    putchar bx, 1, 0

    mov bl, "l"
    putchar bx, 2, 0

    mov bl, "l"
    putchar bx, 3, 0

    mov bl, "o"
    putchar bx, 4, 0

    mov bl, ","
    putchar bx, 5, 0

    mov bl, " "
    putchar bx, 6, 0

    mov bl, "W"
    putchar bx, 7, 0

    mov bl, "o"
    putchar bx, 8, 0

    mov bl, "r"
    putchar bx, 9, 0

    mov bl, "l"
    putchar bx, 10, 0

    mov bl, "d"
    putchar bx, 11, 0

    mov bl, "!"
    putchar bx, 12, 0

    ret