#include <system.h>

/* Function prototypes for all exception handlers
 * The first 32 entries in the IDT are reserved by Intel for exceptions */

extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

/* Access flags ar 0x8E meaning that the entry is present and running in ring 0 and has the lower 5 bits set to the required '14', which is represented by 'E' in hex. */
void isrs_install()
{
	k_printf("ISR: install...\n");
    idt_set_gate(0, (unsigned)isr0, 0x08, 0x8E);
    idt_set_gate(1, (unsigned)isr1, 0x08, 0x8E);
    idt_set_gate(2, (unsigned)isr2, 0x08, 0x8E);
    idt_set_gate(3, (unsigned)isr3, 0x08, 0x8E);
    idt_set_gate(4, (unsigned)isr4, 0x08, 0x8E);
    idt_set_gate(5, (unsigned)isr5, 0x08, 0x8E);
    idt_set_gate(6, (unsigned)isr6, 0x08, 0x8E);
    idt_set_gate(7, (unsigned)isr7, 0x08, 0x8E);
    idt_set_gate(8, (unsigned)isr8, 0x08, 0x8E);
    idt_set_gate(9, (unsigned)isr9, 0x08, 0x8E);
    idt_set_gate(10, (unsigned)isr10, 0x08, 0x8E);
    idt_set_gate(11, (unsigned)isr11, 0x08, 0x8E);
    idt_set_gate(12, (unsigned)isr12, 0x08, 0x8E);
    idt_set_gate(13, (unsigned)isr13, 0x08, 0x8E);
    idt_set_gate(14, (unsigned)isr14, 0x08, 0x8E);
    idt_set_gate(15, (unsigned)isr15, 0x08, 0x8E);
    idt_set_gate(16, (unsigned)isr16, 0x08, 0x8E);
    idt_set_gate(17, (unsigned)isr17, 0x08, 0x8E);
    idt_set_gate(18, (unsigned)isr18, 0x08, 0x8E);
    idt_set_gate(19, (unsigned)isr19, 0x08, 0x8E);
    idt_set_gate(20, (unsigned)isr20, 0x08, 0x8E);
    idt_set_gate(21, (unsigned)isr21, 0x08, 0x8E);
    idt_set_gate(22, (unsigned)isr22, 0x08, 0x8E);
    idt_set_gate(23, (unsigned)isr23, 0x08, 0x8E);
    idt_set_gate(24, (unsigned)isr24, 0x08, 0x8E);
    idt_set_gate(25, (unsigned)isr25, 0x08, 0x8E);
    idt_set_gate(26, (unsigned)isr26, 0x08, 0x8E);
    idt_set_gate(27, (unsigned)isr27, 0x08, 0x8E);
    idt_set_gate(28, (unsigned)isr28, 0x08, 0x8E);
    idt_set_gate(29, (unsigned)isr29, 0x08, 0x8E);
    idt_set_gate(30, (unsigned)isr30, 0x08, 0x8E);
    idt_set_gate(31, (unsigned)isr31, 0x08, 0x8E);
    k_printf("ISR: success\n");
}
/* String array containing the exception messages */
unsigned char *exception_messages[] =
{
	"Interrupt: Division By Zero",
	"Interrupt: Debug",
	"Interrupt: Non Maskable Interrupt",
	"Interrupt: Breakpoint Exception",
	"Interrupt: Into Detected Overflow Exception",
	"Interrupt: Out of Bounds Exception",
	"Interrupt: Invalid Opcode Exception",
	"Interrupt: No Coprocessor Exception",

	"Interrupt: Double Fault",
	"Interrupt: Coprocessor Segment Overrun",
	"Interrupt: Bad TSS",
	"Interrupt: Segment Not Present",
	"Interrupt: Stack Fault",
	"Interrupt: General Protection Fault",
	"Interrupt: Page Fault",	
	"Interrupt: Unknown Interrupt",

	"Interrupt: Coprocessor Fault",
	"Interrupt: Alignment Check",
	"Interrupt: Machine Check",
	"Interrupt: Reserved",
	"Interrupt: Reserved",
	"Interrupt: Reserved",
	"Interrupt: Reserved",
	"Interrupt: Reserved",

	"Interrupt: Reserved",
	"Interrupt: Reserved",
	"Interrupt: Reserved",
	"Interrupt: Reserved",
	"Interrupt: Reserved",
	"Interrupt: Reserved",
	"Interrupt: Reserved",
	"Interrupt: Reserved"
};

void test_assembler_stuff()
{
	k_printf("assembler hi\n");
}

/* Exception handling Interrupt Service Routines will point to this function. All ISRs disable interrupts while they are being serviced as a 'locking' mechanism to prevent an IRQ from happening and messing up kernel data structures */
void fault_handler(struct regs *r)
{
	k_printf("Exception Occured!\n");
    /* Check if the fault is betwee 0 and 31? */
    if (r->int_no < 32)
    {
        /* Display the interrupt description for the Exception and halt the system using an infinite loop */
        k_printf(exception_messages[r->int_no]);
	k_printf("\nSystem Halt\n");
	//go in endless loop for (;;);
	//halt system
	asm volatile("cli; hlt");
    }else{
	/* Here we will handle the hardware interrupts */
    }

}
