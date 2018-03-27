#include "include/system.h"

/* Defining an IDT entry */
struct idt_entry
{
    unsigned short base_lo;	// Offset bits 0-15
    unsigned short sel;       	// Code segment selector in GDT, the kernel segment goes here
    unsigned char always0;   	// Always 0
    unsigned char flags;    	// Type and attributes based on a table
    unsigned short base_hi;	//Offset bits 16-31
} __attribute__((packed));

struct idt_ptr
{
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));

/* Declare an IDT with 256 entries.
 * If an undefined IDT entry is hit it will cause an "unhandled Interrupt" Exception
 * Any descriptor for which the 'Presence' bit is cleared (0) will generate an "Unhandled Interrupt' Exception */
struct idt_entry idt[256];
struct idt_ptr idtp;

/* Load the IDT defined in idtp into the processor */
void idt_load()
{
	__asm__ __volatile__ ("lidt %0" : : "m" (idtp));
}

/* Set entries in the IDT by setting the data for an IDT entry */
void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags)
{
    /* Interrupt routine base address */
    idt[num].base_lo = (base & 0xFFFF);
    idt[num].base_hi = (base >> 16) & 0xFFFF;

    /* The segment or 'selector' that this IDT entry will use
    *  is set here, along with any access flags */
    idt[num].sel = sel;
    idt[num].always0 = 0;
    idt[num].flags = flags;
}

/* Install IDT */
void idt_install()
{
    /* Set special IDT pointer up like in 'gdt.c' */
    idtp.limit = (sizeof (struct idt_entry) * 256) - 1;
    idtp.base = &idt;

    /* Initialize the IDT to zeros */
    k_memset(&idt, 0, sizeof(struct idt_entry) * 256);

    /* Add new IDTs here using idt_set_gate */

    /* Points the processor's internal register to the new IDT */
    idt_load();
}
