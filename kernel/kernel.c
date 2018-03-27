#include "include/system.h"
#include "include/console.h"


void *k_memcpy(void *dest, void *src, int count)
{
	/* Copy 'count' bytes of data from 'src' to 'dest'*/
	const char *sp = (const char *)src;
	char *dp = (char *)dest;
	for(; count != 0; count--) *dp++ = *sp++;
	return dest;
}

void *k_memset(void *dest, char val, int count)
{
	/* Set 'count' bytes in 'dest' to 'val'*/
	char *p = dest;
	for( ; count != 0; count--) {
		*p++ = val;
	}
	return(dest);
}

unsigned short *k_memsetw(unsigned short *dest, unsigned short val, int count)
{
	/* This time: 16-bit 'val' and dest pointer */
	unsigned short *p = (unsigned short *)dest;
	for( ; count != 0; count--) {
		*p++ = val;
	}
	return(dest);
}

/* Read from I/O ports to get data from devices such as the keyboard. */
unsigned char inportb (unsigned short port)
{
    unsigned char rv;
    __asm__ ("in %%dx, %%al" : "=a" (rv) : "d" (port));
    return rv;
}

/* Write to I/O ports to send bytes to devices. Used for example to change the text memory buffer curser position */
void outportb (unsigned short port, unsigned char data)
{
	__asm__ ("out %%al, %%dx" : : "a" (data) , "d" (port));
}

/* Print welcome message */
void k_print_kernel_init()
{
	k_printf("Welcome to Oliver's Operatig System (OOS)\n\n\n");
	k_printf("Start initialization:\n\n");
}

/* Main method called from kernel_start.asm */
/* Does initialization and other testing stuff and then goes to idle mode */
void main(){
	init_video();
	/* Available Color Schemes
	 * 0: White on Black
	 * 1: Black on White
	 * 2: Vintage (Red on Cyan)
	 * 3: Eye Cancer
	 */
	k_set_color_scheme(2);
	k_print_kernel_init();

	k_printf("Video:        done\n");

	//init IDT
	idt_install();
	k_printf("IDT:          done\n");
	
	//init ISRs
	isrs_install();
	k_printf("ISRS:         done\n");

	//init IRQ
	irq_install();
	k_printf("IRQ:          done\n");

	__asm__ __volatile__ ("sti");

	k_printf("Interrupts:   done\n");

	// Test interrupt
//	__asm__ __volatile__ ("int $0");

	timer_install();	
	k_printf("Timer:        done\n");
	keyboard_install();
	k_printf("Keyboard:     done\n\n");

	k_printf("Initialization Successful\n\n");

	k_printf(HELP_MESSAGE);

//	k_printf("Entering Test Mode: \n\n");

/*	k_printf("Wait started.\n");
	timer_wait(18*2); // 2 seconds wait
	k_printf("wait ended.\n");*/

	while(1)
	{
		timer_wait(18*1);
		if (IDLE_OUTPUT){k_printf("idle\n");}
	};
}

