#ifndef SYSTEM_H
#define SYSTEM_H

#include <stdbool.h>

/* kernel.c */

/* Important kernel functions */
void *k_memcpy(void *dest, void *src, int count);
void *k_memset(void *dest, char val, int count);
unsigned short *k_memsetw(unsigned short *dest, unsigned short val, int count);
unsigned char inportb (unsigned short _port);
void outportb (unsigned short _port, unsigned char _data);



/* Code to show the C code what the stack frame looks like after an Interrupt Service Routine was running */
struct regs
{
    unsigned int gs, fs, es, ds;      /* pushed the segs last */
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;  /* pushed by 'pusha' */
    unsigned int int_no, err_code;    /* our 'push byte #' and ecodes do this */
    unsigned int eip, cs, eflags, useresp, ss;   /* pushed by the processor automatically */
};

/* idt.c */
void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags);
void idt_install();

/* isrs.c */
void isrs_install();

/* irq.c */
void irq_install();
void irq_uninstall_handler(int irq);
void irq_install_handler(int irq, void (*handler)(struct regs *r));

/* timer.c */
void timer_install();
void timer_wait(int ticks);

/* keyboard.c */
void keyboard_install();

/* Other */
#define HELP_MESSAGE "\nThe possible commands are:\nh: display this message\nc: clear scren\nv: toggle idle output\ni: test interrupt (divide by zero)\nu: show uptime in seconds\n\n"
bool IDLE_OUTPUT;
int timer_ticks;


#endif
