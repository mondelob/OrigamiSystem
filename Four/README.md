# Four

> BIOS-interrupt vector echo but this time on FASM

*Four* is the same program as [One](../One), but instead uses the FASM
assembler.

## Interrupt vectors

*One* only needs to interrupts from the *BIOS-interrupt vector table*:

* Interrupt vector 0x10 : Function 0x0E - Write character on TTY mode
* Interrupt vector 0x16 : Function 0x00 - Read character

You can read more about this on [Wikipedia](https://en.wikipedia.org/wiki/BIOS_interrupt_call)
