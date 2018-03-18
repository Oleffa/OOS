// Declare external 'main' label (C-Code in kernel.c)
.extern main
 
// Declare the 'start' label as global so that the linker knows where it is
.global start

// Allows the gdt.c to access this code
//get gp from an extern file
.extern gp
//interrupt error codes
.INCLUDE "error_codes.inc"
.extern test_assembler_stuff
.extern fault_handler


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
		//why the fuck do i need this here? This code is never even executed. And Otherwise the interrupt is not processes properly...
		//jmp isr3
		jmp hang
		// In case of an error when calling the main function in the kernel.c:
	hang:
		cli      // Disable CPU interrupts
		hlt      // Halt the CPU
		jmp hang // If that didn't work, loop around and try again.
		//Dividie by zero exception
	isr0:
		cli
		pushl $0 // put 0 as error code to keep all interrupts similar
		pushl $0
		jmp isr_common_stub
	//Debug Exception
	isr1:
		cli
		pushl $0
		pushl $1
		jmp isr_common_stub
	//Non maskable Interrupt Exception
	isr2:
		cli
		pushl $0
		pushl $2
		jmp isr_common_stub
	//Breakpoint exception
	isr3:
		cli
		pushl $0
		pushl $3
		jmp isr_common_stub
	//INTO Detected Overflow Exception
	isr4:
		cli
		pushl $0
		pushl $4
		jmp isr_common_stub
	//Out of Bounds Exception
	isr5:
		cli
		pushl $0
		pushl $5
		jmp isr_common_stub
	//Invalid Opcode Exception
	isr6:
		cli
		pushl $0
		pushl $6
		jmp isr_common_stub
	//Coprocessor not available Exception
	isr7:
		cli
		pushl $0
		pushl $7
		jmp isr_common_stub
	//Double Fault Exception
	isr8:
		cli
		//has error code
		pushl $8
		jmp isr_common_stub
	//Coprocessor Segment Overrun Exception
	isr9:
		cli
		pushl $0
		pushl $9
		jmp isr_common_stub
	//BAD TSS Exception
	isr10:
		cli
		//has error code
		pushl $10
		jmp isr_common_stub
	//Segment not present
	isr11:
		cli
		//has error code
		pushl $11
		jmp isr_common_stub
	//Stack fualt exception
	isr12:
		cli
		//has error code
		pushl $12
		jmp isr_common_stub
	//General protection Fault exception
	isr13:
		cli
		//has error code
		pushl $13
		jmp isr_common_stub
	//Page fault exception
	isr14:
		cli
		//has error code
		pushl $14
		jmp isr_common_stub
	//Reserved Exception
	isr15:
		cli
		pushl $0
		pushl $15
		jmp isr_common_stub
	//Coprocessor Fault
	isr16:
		cli
		pushl $0
		pushl $16
		jmp isr_common_stub
	//Alignment Check Exception
	isr17:
		cli
		pushl $0
		pushl $17
		jmp isr_common_stub
	//Machine Check Exception
	isr18:
		cli
		pushl $0
		pushl $18
		jmp isr_common_stub
	isr19:
		cli
		pushl $0
		pushl $19
		jmp isr_common_stub
	isr20:
		cli
		pushl $0
		pushl $20
		jmp isr_common_stub
	isr21:
		cli
		pushl $0
		pushl $21
		jmp isr_common_stub
	isr22:
		cli
		pushl $0
		pushl $22
		jmp isr_common_stub
	isr23:
		cli
		pushl $0
		pushl $23
		jmp isr_common_stub
	isr24:
		cli
		pushl $0
		pushl $24
		jmp isr_common_stub
	isr25:
		cli
		pushl $0
		pushl $25
		jmp isr_common_stub
	isr26:
		cli
		pushl $0
		pushl $26
		jmp isr_common_stub
	isr27:
		cli
		pushl $0
		pushl $27
		jmp isr_common_stub
	isr28:
		cli
		pushl $0
		pushl $28
		jmp isr_common_stub
	isr29:
		cli
		pushl $0
		pushl $29
		jmp isr_common_stub
	isr30:
		cli
		pushl $0
		pushl $30
		jmp isr_common_stub
	isr31:
		cli
		pushl $0
		pushl $31
		jmp isr_common_stub

	/*
	isr_common_stub:
		//Save CPU state
		push %ebp
		push %edi
		push %esi
		push %edx
		push %ecx
		push %ebx
		push %eax
		// Call handler
		push %esp
		call fault_handler
		add $4, %esp
		// Restore CPU state
		pop %eax
		pop %ebx
		pop %ecx
		pop %edx
		pop %esi
		pop %edi
		pop %ebp
		// Take Error code and Interrupt number from stack
		add $8, %esp
		// Jump back to paused code
		iret
	*/

	isr_common_stub:
		push %ebp
		push %edi
		push %esi
		push %edx
		push %ecx
		push %ebx
		push %eax
		// Save CPU statei
		push %ds
		push %es
		push %fs
		push %gs
		push %eax
		// Call handler
		push %esp
		call fault_handler
		add $4, %esp
		// Restore CPU state
		pop %eax
		pop %gs
		pop %fs
		pop %es
		pop %ds
		pop %eax
		pop %ebx
		pop %ecx
		pop %edx
		pop %esi
		pop %edi
		pop %ebp
		add $8, %esp
		iret


/*
	isr_common_stub:


		pusha
		push %ds
		push %es
		push %fs
		push %gs

		mov $0x10, %ax
		mov %ds, %ax
		mov %es, %ax
		mov %fs, %ax
		mov %gs, %ax
		mov %eax, %esp
		push %eax
		mov fault_handler, %eax
		call *%eax
		pop %eax
		pop %gs
		pop %fs
		pop %es
		pop %ds
		popa
		add %esp, 8
		iret
*/





