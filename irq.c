#include <system.h>

// ISRs that point to the IRQ handler instead of the regular fault handler in isrs.c

extern void irq0(void);
extern void irq1(void);
extern void irq2(void);
extern void irq3(void);
extern void irq4(void);
extern void irq5(void);
extern void irq6(void);
extern void irq7(void);
extern void irq8(void);
extern void irq9(void);
extern void irq10(void);
extern void irq11(void);
extern void irq12(void);
extern void irq13(void);
extern void irq14(void);
extern void irq15(void);

// Array of function pointers. Used to handle custom IRQ handlers for a given interrupt request
void *irq_routines[16] = 
{
	0, 0, 0, 0, 0, 0, 0, 0,
       	0, 0, 0, 0, 0, 0, 0, 0
};

// Installs a custom IRQ handler for the given IRQ
void irq_install_handler(int irq, void (*handler)(struct regs *r))
{
	irq_routines[irq] = handler;
}

// Clear the handler for a given IRQ
void irq_uninstall_handler(int irq)
{
	irq_routines[irq] = 0;
}

// Remaps the IRQs 0-15 to IDT entries 32 to 47 because if we would map IRQ0-7 to IDT entries 8-15 we would use IDT[8]=Double Fault.
// Sends commands to the Programmable Interrupt Controller (PIC)
void irq_remap(void)
{
    outportb(0x20, 0x11); //Master PIC init
    outportb(0x21, 0x20); //Init command for PIC
    outportb(0x21, 0x04); //Interrupt number for IRQ0
    outportb(0x21, 0x01); //IRQ2 slave
    outportb(0xA0, 0x11); //Slave-PIC init
    outportb(0xA1, 0x28); //Init command for PIC
    outportb(0xA1, 0x02); //Interrupt number for IRQ8
    outportb(0xA1, 0x01); //IRQ2 Slave
    outportb(0x21, 0x0);  //Activate (demask) all IRQs
    outportb(0xA1, 0x0);  //Ativate (demask) all IRQs
}

// Remap the interrupt controllers
// Install the appropriate ISRs to the correct IDT entries
// Same as for installing the exception handlers
void irq_install()
{
	k_printf("IRQ: install...\n");
	irq_remap();
	
	idt_set_gate(32, (unsigned)irq0, 0x08, 0x8E);
	idt_set_gate(33, (unsigned)irq1, 0x08, 0x8E);
	idt_set_gate(34, (unsigned)irq2, 0x08, 0x8E);
	idt_set_gate(35, (unsigned)irq3, 0x08, 0x8E);
	idt_set_gate(36, (unsigned)irq4, 0x08, 0x8E);
	idt_set_gate(37, (unsigned)irq5, 0x08, 0x8E);
	idt_set_gate(38, (unsigned)irq6, 0x08, 0x8E);
	idt_set_gate(39, (unsigned)irq7, 0x08, 0x8E);
	idt_set_gate(40, (unsigned)irq8, 0x08, 0x8E);
	idt_set_gate(41, (unsigned)irq9, 0x08, 0x8E);
	idt_set_gate(42, (unsigned)irq10, 0x08, 0x8E);
	idt_set_gate(43, (unsigned)irq11, 0x08, 0x8E);
	idt_set_gate(44, (unsigned)irq12, 0x08, 0x8E);
	idt_set_gate(45, (unsigned)irq13, 0x08, 0x8E);
	idt_set_gate(46, (unsigned)irq14, 0x08, 0x8E);
	idt_set_gate(47, (unsigned)irq15, 0x08, 0x8E);
	
	k_printf("IRQ: success\n");
}

// IRQs point to this function (from start.S)
// 
void irq_handler(struct regs *r)
{
	k_printf("IRQ occured...\n");
	// Blank function pointer
	void (*handler)(struct regs *r);
	// Find out if there is a custom handler and run it
	handler = irq_routines[r->int_no - 32];
	k_printf("made it 1\n");
	if (handler)
	{	
		k_printf("made it 2\n");
		handler(r);
	}
	k_printf("made it 3\n");
	// If the IDT entry is > 40 (IRQ8-15 have been called) we need to send an "End Of Interrupt" command to the slave IRQ controller
	// There are two 8259 chips: The first at 0x20 and 0xA0.
	// If no EOI is sent no more IRQs will be raised
	if (r->int_no >= 0x28) //0x28 = 40
	{
		outportb(0xA0, 0x20);
	}

	// Finally always send an EOI to the master interrupt controller
	outportb(0x20, 0x20);
	k_printf("IRQ handled\n");
}















