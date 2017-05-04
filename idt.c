#include "include/console.h"
#include "include/idt.h"
#include "include/system.h"
#include <string.h>
#define IDT_ENTRIES 256

struct idt_entry
{
	unsigned short base_lo;
	unsigned short sel;		//kernel segment
	unsigned char always0;		//always 0
	unsigned char flags; 		//using the flags table
       	unsigned short base_hi;	
} __attribute__((packed));

struct idt_ptr
{
	unsigned short limit;
	unsigned int base;
} __attribute__((packed));

/*declare an idt of 256 entries.
 * not all will be used but if an undefined idt entry is hit there will be an exception
 */
struct idt_entry idt[IDT_ENTRIES];
struct idt_ptr idtp;

void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags){
	//take base and split in high and low 16 bit
	idt[num].base_lo = base & 0xFFFF;
	idt[num].base_hi = (base >> 16) & 0xFFFF;
	
	//rest of the fields
	idt[num].sel = sel;
	idt[num].always0 = 0;
	idt[num].flags = flags | 0x60;
}

void idt_install(void){
	kprintf("setting up idt...");
	//set up idt pointer
	idtp.limit = (sizeof (struct idt_entry) * 256) - 1;
	idtp.base = &idt;

	//clear the entire idt and init it with 0
	memset_char(&idt, 0, sizeof(struct idt_entry) * 256);
	
	//add new ISRs to the idt here using idt_set_gate
	
}

//load the idt
void init_idt(){
	idt_install();
	asm volatile("lidt %0" : : "m" (idtp));
	kprintf("success!");
}


