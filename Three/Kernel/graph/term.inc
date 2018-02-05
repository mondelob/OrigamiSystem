; term.inc - Terminal macros and subroutines
; 2018-02-05
; Bruno Mondelo Giaramita

include "vga.inc"

section ".bss"
x_pos: db 1
y_pos: db 1

section ".text"

nextline:                        ; Jumps to the next line
    mov byte [x_pos], 0          ; Sets horizontal position to zero
    inc byte [y_pos]             ; Adds one vertical line
    ret

cprint:                          ; Prints a character
                                 ; AH: Attributtes
                                 ; AL: Character
    push ebx                     ; Store EBX register
    push ecx                     ; Store ECX register
    mov ebx, [x_pos]             ; Set EBX to horizontal position
    mov ecx, [y_pos]             ; Set ECX to vertical position
    call putchar                 ; Call VGA function
    pop ebx                      ; Restore EBX register
    pop ecx                      ; Restore ECX register
    inc byte [x_pos]             ; Increment horizontal line by one
    cmp byte [x_pos], VGA_WIDTH  ; Compare with the maximum elements on line
    jz nextline                  ; Jump to next line
    ret


macro sprint s {
    mov ah, 0x85
    
    mov al, "H"
    call cprint

    mov al, "e"
    call cprint
}

init_term:
    mov byte[x_pos], 0           ; Set horizontal position to 0
    mov byte[y_pos], 1           ; Set vertical position to 0
    ret