; vga.inc - VGA macros, symbols and subroutines
; 2018-01-26
; Bruno Mondelo Giaramita

VIDEO_MEMORY      = 0xB8000      ; Symbolic constant pointing to the video
                                 ; memory
VGA_WIDTH         = 80           ; VGA screen max width
VGA_HEIGHT        = 25           ; VGA screen max height

; VGA colors enumeration
VGA_BLACK         = 0x0
VGA_BLUE          = 0x1
VGA_GREEN         = 0x2
VGA_CYAN          = 0x3
VGA_RED           = 0x4
VGA_MAGENTA       = 0x5
VGA_BROWN         = 0x6
VGA_LIGHT_GRAY    = 0x7
VGA_GRAY          = 0x8
VGA_LIGHT_BLUE    = 0x9
VGA_LIGHT_GREEN   = 0xA
VGA_LIGHT_CYAN    = 0xB
VGA_LIGHT_RED     = 0xC
VGA_LIGHT_MAGENTA = 0xD
VGA_YELLOW        = 0xE
VGA_WHITE         = 0xF

section ".text"

; THIS SHOULD BE A MACRO : TODO
putchar:                         ; Puts a character on the video memory
                                 ; AX: character
                                 ; EBX: x positon
                                 ; ECX: y positon
    push ebx                     ; Store EBX register
    push ecx                     ; Store ECX register
    push edx                     ; Store EDX register
    mov edx, VIDEO_MEMORY        ; Point to video memory
    imul ebx, 2                  ; Every entry is two bytes
    add edx, ebx                 ; Add horizontal offset
    imul ecx, 2                  ; Entries are two bytes
    imul ecx, VGA_WIDTH          ; Multiply per line width
    add edx, ecx                 ; Add vertical offset
    mov [edx], ax                ; Add entry to memory array
    pop ebx                      ; Restore EBX
    pop ecx                      ; Restore ECX
    pop edx                      ; Restore EDX
    ret

vga_color:                       ; Sets the AH register to the color attributte
                                 ; given it's foreground and background colors
                                 ; BH : foreground color
                                 ; BL : background color
    push bx                      ; Store BL on the stack
    mov ah, bl                   ; Set AH register to the background color
    shl ah, 4                    ; Shift four positions the AH register
    or ah, bh                    ; Or with the foreground color
    pop bx                       ; Restore the BL register
    ret