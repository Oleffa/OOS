#include <inttypes.h>

extern void init_idt(void);
extern void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags);
