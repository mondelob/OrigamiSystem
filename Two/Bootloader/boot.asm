; boot.asm
; 2017-11-06
; Bruno Mondelo Giaramita
; Multiboot bootloader
; Declare multiboot constants
MBALIGN   equ   1<<0                ; Align loaded modules on page boundaries
MEMINFO   equ   1<<1                ; Memory mapping
FLAGS     equ   MBALIGN | MEMINFO   ; Multiboot flag field
MAGIC     equ   0x1BADB002          ; Magic number to let bootloader find header
CHECKSUM  equ   -(MAGIC + FLAGS)    ; Checksum to check the multiboot

; Declare the multiboot header. This will let the bootloader know this is a
; kernel. Those are standards on the multiboot
section .multiboot
align 4
  dd MAGIC
  dd FLAGS
  dd CHECKSUM

; Multiboot doesn't declare the stack. This will allocate memory for a small
; stack allocating 16 KiB at the bottom
section .bss
align 16
stack_bottom:
resb 16384
stack_top:

; Linker will specify the start function defined here. We are already on
; protected mode due to the bootloader
section .text
global _start:function (_start.end - _start)
_start:

  ; Set up the stack; ESP register must point to the top of the stack
  mov esp, stack_top

  ; GDT should be loaded here

  ; Call the high level kernel
  extern kernel_main
  call kernel_main

  ; End the boot: disable interrupts and let the system on halt
  cli
.hang:  hlt
  jmp .hang
.end:
