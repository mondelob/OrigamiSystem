; boot.asm
; Shows a message on the boot sequence and proceeds to load the Kernel

    cli             ; Ignore all other interrupts
[ORG 0x7C00]        ; Set an offset to the address 0x07C0. This address
                    ; is where the bootloader is expected.
    xor ax, ax      ; Set AX register to zero
    mov ds, ax      ; Copy this register to the DS segment
    mov ss, ax      ; Set the Stack Selector to 0. Stack starts at 0
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov sp, 0x7FFF  ; Past code start

    cld             ; #####################################################

    mov ax, 0xB800  ; Set the text video memory
    mov es, ax      ; Set the Extended to the video memory

    mov si, msg     ; Set the message
    call sprint

hang:
    jmp hang

dochar:
    call cprint

sprint:
    lodsb           ; Load the character into AL register
    cmp al, 0       ; Compare the AL character to the NUL character
    jne dochar      ; On the case is not zero print the character
    mov byte [xpos], 0  ; Go back to left
    add byte [ypos], 1  ; Add one the the vertical
    ret

cprint:
    mov ah, 0x0F    ; Set the attribute of the printing. First hex for the
                    ; background color, and the second one for the foreground
    mov cx, ax      ; Save character and attribute
    movzx ax, byte [ypos]  ; Move the window to the actual vertical value
    mov dx, 160     ; Set 2 bytes character and attribute
    mul dx          ; 80 columns
    movzx bx, byte [xpos]  ; Set the horizontal value
    shl bx, 1       ; Move the horizontal by one character

    mov di, 0       ; Start video memory
    add di, ax      ; Add vertical offset
    add di, bx      ; Add horizontal offset

    mov ax, cx      ; Restore character and attribute
    stosw           ; Write character and attribute
    add byte [xpos], 1  ; Advance one character to right

    ret

xpos db 0           ; The horizontal position for writing
ypos db 0           ; The vertical position for writing

msg db "Hello World!", 0

times 510-($-$$) db 0
db 0x55
db 0xAA
