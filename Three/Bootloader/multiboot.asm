; boot.asm - Simple post-grub loader
; 2018-01-25
; Bruno Mondelo Giaramita

format elf                       ; Specify output format ELF
use32                            ; 32 Bit code

extrn kernel_main                ; External kernel function
public _start                    ; Set the _start label to be globally visible
                                 ; for the linker

MBALIGN   = (1 shl 0)            ; Align modules on page boundaries
MEMINFO   = (1 shl 1)            ; Memory mapping
FLAGS     = (MBALIGN or MEMINFO) ; Multiboot flag
MAGIC     = 0x1BADB002           ; Magic number to be visible for bootloader 
CHECKSUM  = (0 - MAGIC - FLAGS)  ; Check the multiboot
STACKSIZE = 0x4000               ; Set the size to the stack to 16K

; Multiboot standards
.multiboot:
align 4
    dd MAGIC
    dd FLAGS
    dd CHECKSUM

; Allocate space for a 16k stack
section '.bss'
align 4
_stack:
    rb STACKSIZE

; Linker will start here
; Already on protected mode
section '.text'
_start:
    mov esp, _stack + STACKSIZE  ; Point the stack pointer to
                                 ; the top of the stack
    ; LOAD GDT

    push eax                     ; Pass multiboot magic
    push ebx                     ; Pass multiboot info
    
    call kernel_main             ; Call the high level kernel

    cli                          ; Disable all interrupts
hang: hlt                        ; Hang the system
    jmp hang

; End multiboot
fi:
