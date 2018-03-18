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
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}

/* We will use this to write to I/O ports to send bytes to devices. This
*  will be used in the next tutorial for changing the textmode cursor
*  position. Again, we use some inline assembly for the stuff that simply
*  cannot be done in C */
void outportb (unsigned short _port, unsigned char _data)
{
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}

void test_stuff() {
	k_printf("Entering test mode!");
//	for (int j = 0; j < 26; j++){
//		k_printf("0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29x");
//	}
	k_printf("test");
	k_printf("test");
	k_printf("0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,2x"); 
}

/* This is a very simple main() function. All it does is sit in an
*  infinite loop. This will be like our 'idle' loop */
void main()
{
    /* You would add commands after here */
	init_video();
	gdt_install();
	test_stuff();
   /* ...and leave this loop in. There is an endless loop in
    *  'start.asm' also, if you accidentally delete this next line */
    for (;;);
}
