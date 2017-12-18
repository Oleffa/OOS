#include "include/system.h"
#include "include/console.h"

unsigned char *memset_char(unsigned char *dest, unsigned char val, int count){
	unsigned char *p = dest;
	while(count > 0){
		*p = val;
		p++;
		count--;
	}
	return(dest);
}

unsigned short *memset_short(unsigned short *dest, unsigned short val, int count){
	if(dest != 0 && count > 0){
		unsigned short *p = dest;
		while(count > 0){
			*p = val;
			p++;
			count--;
		}
	}
	return(dest);
}
/*used to write to I/O ports by sending bytes to the devices, used for changing textmode cursor postition */
void outportb(unsigned short _port, unsigned char _data){
	__asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}
/*used to read from I/O prots to get data from devices like keyboard*/
unsigned char inportb(unsigned short _port){
	unsigned char rv;
	__asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
	return rv;
}

unsigned char *kmemcopy(unsigned char *dest, const unsigned char *src, int count){
	int i;
	char* d = (char*) dest;
	char* s = (char*) src;
	for(i = 0; i < count; i++){
		*s++ = *d++;
	}	
	return(dest);
}
/*idle loop in main method*/
void main(){
	for(;;);
}
