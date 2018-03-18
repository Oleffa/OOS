// Declare external 'main' label (C-Code in kernel.c)
.extern main
 
// Declare the 'start' label as global so that the linker knows where it is
.global start

// Allows the gdt.c to access this code
.global gdt_flush
//get gp from an extern file
.extern gp
 
// GRUB, needs to know some basic information about our kernel before it can boot it by using the multiboot standard
// To define a valid 'Multiboot header' that will be recognised by GRUB, we need to hard code some
// constants into the executable. The following code calculates those constants.

.set MB_MAGIC, 0x1BADB002          // This is a 'magic' constant that GRUB will use to detect our kernel's location.
.set MB_FLAGS, (1 << 0) | (1 << 1) // This tells GRUB to 1: load modules on page boundaries and 2: provide a memory map (this is useful later in development)

// Finally, we calculate a checksum that includes all the previous values
.set MB_CHECKSUM, (0 - (MB_MAGIC + MB_FLAGS))
 
// We now start the section of the executable that will contain our Multiboot header
.section .multiboot
	.align 4 // Make sure the following data is aligned on a multiple of 4 bytes
	// Use the previously calculated constants in executable code
	.long MB_MAGIC
	.long MB_FLAGS
	// Use the checksum we calculated earlier
	.long MB_CHECKSUM
 
// This section contains data initialised to zeroes when the kernel is loaded
.section .bss
	// Allocate 4096 bytes (or 4 Kilobytes) for our stack.
	// Can be extended later
	.align 16
	stack_bottom:
		.skip 4096 // Reserve a 4096-byte (4K) stack
	stack_top:
 
// Contains the assembly code to be run when the kernel loads
.section .text
	// Start label defines the first code being executed when the kernel is loaded
	start:
		// First set up a C environment. All this needs is a stack.
		mov $stack_top, %esp // Set the stack pointer to the top of the stack
 
		// At this point, we can call our main C function. And we can call our C code
		call main
 
		// In case of an error when calling the main function in the kernel.c:
		hang:
			cli      // Disable CPU interrupts
			hlt      // Halt the CPU
			jmp hang // If that didn't work, loop around and try again.

