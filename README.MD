# Oli's Operating System (OOS)
OOS is a hobby operating system and my first shot at OS development. 

It features a simple bootloader written in assembly and a basic 32-bit kernel written in C.

![Screenshot](/images/001.jpg)

## Features
- Small Bootloader written in assembly
- Writing to video buffer
- Interrupt driven timer
- Basic Keyboard input support
- Video buffer color schemes

## How to use
- Requires QEMU, GCC (i used a cross compiler for i686-elf: https://wiki.osdev.org/GCC_Cross-Compiler), NASM
- Run `make` to generate os.img
- Run `make run` to run the os in QEMU

## Code
- boot/ contains assembly code for the bootloader and Global Descriptor Table initialization
- kernel/ contains kernel code written in C and some assembly code for interrupts and to initialize the C environment

## TODO
- Write console application
- Get the OS to run on actual hardware
- Fix the uptime output (integer to string function)
- Add function to switch color schemes
- What next (Memory manager, VGA driver, device interface, file system support and disk drives to access files and open applications, multitasking support)

## Used Tutorials:
- lowlevel.eu: http://www.lowlevel.eu/wiki/ (German)
- osdev.org: http://wiki.osdev.org/Tutorials
- Brans kernel tutorial: http://www.osdever.net/tutorials/view/brans-kernel-development-tutorial
