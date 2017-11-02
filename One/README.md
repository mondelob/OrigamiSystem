# One

> Simple BIOS-interrupt vector echo

*One* is not an **Operative System**, is not even a **bootloader**; it's a
simple program that using the *BIOS-interrupt vector table* echoes back
all the input messages.

## Interrupt vectors

*One* only needs to interrupts from the *BIOS-interrupt vector table*:

* Interrupt vector 0x10 : Function 0x0E - Write character on TTY mode
* Interrupt vector 0x16 : Function 0x00 - Read character

You can read more about this on [Wikipedia](https://en.wikipedia.org/wiki/BIOS_interrupt_call)
