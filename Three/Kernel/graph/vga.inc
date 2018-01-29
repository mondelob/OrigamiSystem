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

macro putchar ucc, x, y {        ; Macro to send a character to the video memory
                                 ; ucc is the character, while x and y are the
                                 ; positions on the screen
    mov edx, VIDEO_MEMORY        ; Set register to point to video memory
    add edx, (y * 2) * VGA_WIDTH ; Add Y offset of the character on the screen
    add edx, x * 2               ; Add X offet of the character on the screen
    mov [edx], ucc               ; Set character
}

vga_color:                       ; Sets the AH register to the color attributte
                                 ; given it's foreground and background colors
                                 ; BH : foreground color
                                 ; BL : background color
    mov ah, bl                   ; Set AH register to the background color
    shl ah, 4                    ; Shift four positions the AH register
    or ah, bh                    ; Or with the foreground color
    ret