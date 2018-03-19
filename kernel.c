#include <system.h>

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

int strlen(const char *str)
{
    /* Returning how many characters it needs to check before it finds a 0. Return length of the string in bytes */
	int i;
	for (i = 0; *str != '\0'; str++){i++;}
	return i;
}

/* We will use this later on for reading from the I/O ports to get data
*  from devices such as the keyboard. We are using what is called
*  'inline assembly' in these routines to actually do the work */
unsigned char inportb (unsigned short _port)
{
    unsigned char rv;
    asm volatile ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}

/* We will use this to write to I/O ports to send bytes to devices. This
*  will be used in the next tutorial for changing the textmode cursor
*  position. Again, we use some inline assembly for the stuff that simply
*  cannot be done in C */
void outportb (unsigned short _port, unsigned char _data)
{
//    asm volatile ("outb %1, %0" : : "dN" (_port), "a" (_data));
	asm volatile("outb %0, %1" : : "a" (_data), "Nd" (_port));
}

void test_stuff() {
	k_printf("\nEntering test mode!\n");

	k_printf("dividing by 0 what could go wrong...\n");
	int x = 10/0;
	k_printf("I guess it worked....\n");
//	for (int j = 0; j < 26; j++){
//		k_printf("0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29x");
//	}
//	k_printf("0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29x");
}
/* Executes stuff and then goes into idle mode */
void main()
{
//	gdt_install();
	init_video();
	k_printf("Welcome to Oliver's Operating System\n\n");
	k_printf("Initializing Kernel:\n\n");
	gdt_install();
	idt_install();
	isrs_install();
	irq_install();
	//enable hw interrupts
	__asm__ __volatile__ ("sti");

	__asm__ __volatile__ ("int $0");

	k_printf("======================================");

	timer_install();

//	test_stuff();
	k_printf("Falling back to idle...\n");
//	for (;;);
}
