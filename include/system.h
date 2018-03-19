#ifndef __SYSTEM_H
#define __SYSTEM_H

/* MAIN.C */
void *k_memcpy(void *dest, void *src, int count);
void *k_memset(void *dest, char val, int count);
unsigned short *k_memsetw(unsigned short *dest, unsigned short val, int count);
extern int strlen(const char *str);
extern unsigned char inportb (unsigned short _port);
extern void outportb (unsigned short _port, unsigned char _data);

/* Console functions */
extern void k_cls();
extern void k_putch(unsigned char c);
extern void k_printf(unsigned char *str);
extern void k_printf_1();
extern void settextcolor(unsigned char forecolor, unsigned char backcolor);
extern void init_video();

/* GDT functions */
extern void gdt_set_gate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran);
extern void gdt_install();

/* IDT functions */
extern void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags);
extern void idt_install();

/* isrs */
/* Defines what the stack looks like after an ISR was running */
struct regs
{
//    unsigned int gs, fs, es, ds;      /* pushed the segs last */
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;  /* pushed by 'pusha' */
    unsigned int int_no, err_code;    /* our 'push byte #' and ecodes do this */
    unsigned int eip, cs, eflags, useresp, ss;   /* pushed by the processor automatically */
};

extern void isrs_install();

/* IRQ functions */
extern void irq_install();
extern void irq_install_handler();
extern void irq_uninstall_handler();

/* Timer functions */
extern void timer_install();

#endif
