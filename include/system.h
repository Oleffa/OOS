#ifndef __SYSTEM_H
#define __SYSTEM_H

extern unsigned short *kmemcopy(unsigned short *dest, unsigned short *src, int count);
extern unsigned char *memset_char(unsigned char *dest, unsigned char val, int count);
extern unsigned short *memset_short(unsigned short *dest, unsigned short val, int count);
extern void outportb(unsigned short _port, unsigned char _data);
extern void settextattributes(unsigned char text, unsigned char background);
#endif
