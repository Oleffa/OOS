#include "include/console.h"
#include "include/idt.h"

#define IDT_ENTRIES 256

static uint64_t idt[IDT_ENTRIES];

struct {
	uint16_t limit;
	void* pointer;
} __attribute__((packed)) idtp = {
	.limit = IDT_ENTRIES * 8 - 1,
	.pointer = idt,
};
static void load_idt() {
	asm volatile("lidt %0" : : "m" (idtp));
}
void int_handler(void) {
	kprintf("Interrupt!\n");
	while(1);
}
void init_idt(void){
	load_idt();
}
