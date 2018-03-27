#include "include/system.h"

/* Interrupt service requests (IRQs) are interrupts raised by hardware devices */

/* Interrupt Service Routines that point to the IRQ handler instead of the regular fault handler in isrs.c (Isrs contains interrupts related to exceptions that the processor can encounter when normal execution cannot continue) */
extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

/* Define an array of function pointers that are used to handle the custom IRQ handlers that can be defined using irq_install_handler */
void *irq_routines[16] =
{
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0
};

/* Installs a custom IRQ andler for the given IRQ */
void irq_install_handler(int irq, void (*handler)(struct regs *r))
{
    irq_routines[irq] = handler;
}

/* Removes the handler of a given IRQ */
void irq_uninstall_handler(int irq)
{
    irq_routines[irq] = 0;
}

/* Remaps the first 16 (0-15) IRQs to IDT entries 32 to 47 in order to not overwrite the exception ISRs */
void irq_remap(void)
{
    outportb(0x20, 0x11);
    outportb(0xA0, 0x11);
    outportb(0x21, 0x20);
    outportb(0xA1, 0x28);
    outportb(0x21, 0x04);
    outportb(0xA1, 0x02);
    outportb(0x21, 0x01);
    outportb(0xA1, 0x01);
    outportb(0x21, 0x0);
    outportb(0xA1, 0x0);
}

/* Remap Interrupt controllers */
/* Install lthe appropriate ISRs to the correct IDT entries after remapping them */
void irq_install()
{
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
}

/* IRQs point to this function from kernel_entry.asm */
void irq_handler(struct regs *r)
{
    /* Blank function pointer */
    void (*handler)(struct regs *r);

    /* Check if it is a custom or service interrupt and run it */
    handler = irq_routines[r->int_no - 32];
    if (handler)
    {
        handler(r);
    }

    /* If the IDT entry that was invoked was greater than 40
    *  (meaning IRQ8 - 15), then we need to send an EOI to
    *  the slave controller */#
    /* If the invoked IDT entry was >= than 40 a custom interrupt was invoked and the slave controller also needs a end of interrupt signal */
    if (r->int_no >= 40)
    {
        outportb(0xA0, 0x20);
    }

    /* In both cases an EOI signal has to be sent to the master interrupt controller too */
    outportb(0x20, 0x20);
}
