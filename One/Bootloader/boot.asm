; boot.asm
; Shows a message on the boot sequence and proceeds to load the Kernel

    cli             ; Ignore all other interrupts
[ORG 0x7C00]        ; Set an offset to the address 0x07C0. This address
                    ; is where the bootloader is expected.
    xor ax, ax      ; Set AX register to zero
    mov ds, ax      ; Copy this register to the DS segment

    mov si, msg     ; Copy the message on the SI register
ch_loop:lodsb       ; Loads a word on the AL (A Lower) register from SI register
    or al, al       ; Checks for no word loaded
    jz hang         ; Checks the ZF (Zero Flag) for a conditional jump to hang
    mov ah, 0x0E    ; Assign the 0x0E function: Display character
    int 0x10        ; Call the interrupt
    jmp ch_loop     ; Continue printing the next byte

hang:
    jmp hang

msg db "Hello World!", 13, 10, 0

    times 510-($-$$) db 0
    db 0x55
    db 0xAA
