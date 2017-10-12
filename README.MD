# First attempt on writing an operating system from scratch

## Features:

- booting kernel in qemu or using grub
  - kernel print method to output text to screen/in video buffer
- global descriptor table
- interrupt descriptor table

## TODO:
  - interrupts and the interrupt service routines (isrs), http://wiki.osdev.org/ISRs_PIC_And_Multitasking, http://www.osdever.net/tutorials/view/brans-kernel-development-tutorial
  - comment everything and go through:
    - makefile
    - linker
    - start
  - rework and comment gdt (asm volatile stuff)
  - fix the kernel print method
    - fix the scroll mode -> using memcopy
  - add support for all symbols in terminal

## Used Tutorials:
- lowlevel.eu:              http://www.lowlevel.eu/wiki/Teil_4_-_Hello_World
- osdev.org:                http://wiki.osdev.org/Tutorials
- brans kernel tutorial:    http://www.osdever.net/tutorials/view/brans-kernel-development-tutorial
