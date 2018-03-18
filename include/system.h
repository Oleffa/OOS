#ifndef __SYSTEM_H
#define __SYSTEM_H

/* MAIN.C */
void *k_memcpy(void *dest, void *src, int count);
void *k_memset(void *dest, char val, int count);
unsigned short *k_memsetw(unsigned short *dest, unsigned short val, int count);
extern int strlen(const char *str);
extern unsigned char inportb (unsigned short _port);
extern void outportb (unsigned short _port, unsigned char _data);

// Console stuff
extern void k_cls();
extern void k_putch(unsigned char c);
extern void k_printf(unsigned char *str);
extern void settextcolor(unsigned char forecolor, unsigned char backcolor);
extern void init_video();
//gdt stuff
extern void gdt_set_gate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran);
void gdt_install();
#endif
