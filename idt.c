#include <system.h>

/* Defines an IDT entry */
/* The first entry at zero offset is used in the IDT
 * There are 256 Interrupts 0-255, it can contain less than 256 but calling unused ones can cause a unhandled interrupt event
 */
struct idt_entry
{
    unsigned short base_lo;    /* Offset bits 0-15 */
    unsigned short sel;        /* Code segment selector in GDT or LDT, the kernel segment goes here */
    unsigned char zero;     /* Always 0 */
    unsigned char flags;       /* Type and attributes based on a table */
    unsigned short base_hi;    /* Offset bits 16-31 */
} __attribute__((packed));

struct idt_ptr
{
    unsigned short limit;
    void* base;
} __attribute__((packed));

struct idt_entry idt[256];
struct idt_ptr idtp;

/* Used to load the IDT */
void idt_load()
{
	asm volatile("lidt %0" : : "m" (idtp));
}

/* Set an entry in the IDT */
void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags)
{
    /* Split base up into a high and low 16-bits, storing them in idt[num].base_hi and base_lo.*/
	idt[num].base_hi = (base>>16) & 0xFFFF;	//Interrupt routine base address
	idt[num].sel = sel;		//Selector of IDT
	idt[num].zero = 0;		
	idt[num].flags = flags | 0x60;		//Access Flags
	idt[num].base_lo = (base & 0xFF);	//Interrupt routine base address
}

/* Installs the IDT */
void idt_install()
{
	k_printf("IDT: install...\n");
    /* Set special IDT pointer up like in gdt.c */
    idtp.limit = (sizeof (struct idt_entry) * 256) - 1;
    idtp.base = &idt;

    /* Initializing IDT to zeros */
    k_memset(&idt, 0, sizeof(struct idt_entry) * 256);

    /* Add any new ISRs to the IDT here using idt_set_gate */


    /* Points the processor's internal register to the new IDT */
    idt_load();
    k_printf("IDT: success\n");
}





