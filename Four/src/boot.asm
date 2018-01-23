; boot.asm
; 2018-01-23
; Bruno Mondelo Giaramita
; boot.asm - Boots the system, and after showing a welcome message
; echoes all user messages.
; All of this functions, show and read messages, are done calling the main
; BIOS functions:
; - Interrupt vector 0x10 : Function 0x0E - Write character on TTY mode
; - Interrupt vector 0x16 : Function 0x00 - Read character

format binary         ; Set the assembly output format
use16                 ; The output it's intended to be 16 bit code

org 0x7C00            ; Offset to the bootloader address

    xor ax, ax        ; Set AX register to zero
    mov ds, ax        ; Set DS register to zero
    mov ss, ax        ; Set stack to zero
    mov sp, 0x7C00    ; Stack pointer points to the bootloader entry
    cli               ; Set direction flag
    jmp main          ; Start main program

return:               ; Function to return
    ret

printc:               ; Prints a character byte located in AL register
    mov ah, 0x0E      ; Set the BIOS function
    int 0x10          ; Call the BIOS interrupt vector
    ret

printf:               ; Prints a string pointed by the SI register
    lodsb             ; Load the character
    or al, al         ; Check for the NUL terminator
    jz return         ; Return on the end
    call printc       ; Print the character
    jmp printf        ; Continue printing

newline:              ; Adds a new line
    mov al, 13        ; Set AL to the CR character
    call printc       ; Show the character
    mov al, 10        ; Set AL to the vertical tab character
    call printc       ; Show the character
    ret

assign:               ; Assigns the content of AL on SI registers
    mov [si], al      ; Set AL to the SI content
    inc si            ; Increment SI on the array
    ret

readf:                ; Reads the user input
    xor ah, ah        ; Set AH register to 0
    mov ax, 0x00      ; Set the BIOS function read from keyboard
    int 0x16          ; Call the interrupt vector
    cmp al, 13        ; Compare the input character to CR
    jz clear          ; Return to the main function
    cmp al, 27        ; Compare the input character to ESC
    jz fi             ; Go to the end function on ESC
    call printc       ; Show input character
    call assign       ; Append the character
    jmp readf         ; Read again

clear:                ; Clears the input array actual position
    mov al, 0         ; Assign AL register to NULL character
    call assign       ; Assign the character
    ret

echoloop:             ; Reads the user input and echoes back the message
    mov si, usermsg   ; Move user message to the SI register
    call readf        ; Read the keyboard
    call newline      ; Show a newline
    mov si, usermsg   ; Move the user message to SI register
    call printf       ; Show the user message
    call newline      ; Show a newline
    mov si, usermsg   ; Move the user message to SI register
    call clear        ; Clear usermsg
    jmp echoloop      ; Continue bucle

main:                 ; The main program
    mov si, hellomsg  ; Assign the hellomsg to the SI register
    call printf       ; Call the print function
    call newline      ; Show a newline
    call echoloop     ; Call the echo message loop

fi:                   ; The end program: hang
    mov si, byemsg    ; Assign the byemsg to the SI register
    call printf       ; Call the print function
    call newline      ; Show a newline

hang:                 ; The hang function
    hlt               ; Halt the exection
    jmp hang          ; In case halt continues go again to halt

hellomsg db 'Hello World!', 0
byemsg db 'Bye! :D', 0
usermsg: times 64 db 0
times 510-($-$$) db 0
db 0x55
db 0xAA
