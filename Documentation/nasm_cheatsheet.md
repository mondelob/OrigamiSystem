# NASM Assembly Cheatsheet
> Cheatsheet of the basic Assembly in NASM assembler

* [Instruction syntax](#instruction-syntax)
* [Basic instructions](#basic-instructions)
  * [MOV](#mov)
  * [ADD](#add)
  * [SUB](#sub)
  * [INC and DEC](#inc-and-dec)


## Instruction syntax

The basic Assembly syntax for an **instruction** is the following:

```asm
mnemonic operand(s)   ; Coments are done with the semicolon at the start
```

*mnemonic* is the instruction function while *operands(s)* are a coma-separated
list of the intruction arguments. In general the number of operands for an
**Assembly** function is 0-3 arguments. The types of the operands can be:

* register
* memory
* immediate
* implied

## Basic instructions

### MOV

The most basic instruction is the **MOV** instruction. This instruction could
be compared to the assignment in high level languages. It requires of two
*operands* the destination operand and the source operand:

```asm
mov dest, src
```

the contents of the *src* operand will be copied to the *dest* operand. **MOV**
function have restrictions:

  * Both operands canno't be *memory operands*
  * The operands must be of the same size

### ADD

The **ADD** instruction is used to add integers into the *operand*. Requires of
two arguments the source and the destination.

```asm
add dest, src
```

the contents of *dest* and *src* will be added and they will be stored in
*dest*.

### SUB

As you can suppose **SUB** instruction is the opposite of the *ADD* instruction,
and also requires two arguments

```asm
sub dest, src
```

this will substract *src* from *dest*.

### INC and DEC

The **INC** and **DEC** instructions *adds* or *substracts* one to the
*operands*.

```asm
inc dest
dec dest
```

the first instruction will cause to *dest* operand to be incremented by one. The
second one will substract or decrement this one from *dest*. This operation can
be done by the **ADD** and **SUB** functions, but for the machine **INC** and
**DEC** is more easier to process for the processor.

### Examples

```asm
mov eax, 5    ; Store 3 into EAX register
mov bx, ax    ; Store the value of AX into BX registers

add cx, 7     ; Adds 7 to the CX register
add dx, ax    ; Adds the AX register to the DX register

sub ebx, 3    ; Substracts 3 to the EBX register
sub ecx, eax  ; Substract EAX register to EXC register

inc bx        ; Increments by one the value of the BX register
dec cx        ; Decrements by one the value of the CX register
```
