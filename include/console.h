#include <inttypes.h>
#ifndef CONSOLE_H
#define CONSOLE_H

void kclear(void);
void kprintf(const char* c);
void kprintchar(unsigned char c);
void scrollUP(int lines);
void displaycursor(uint8_t col, uint8_t row);
#endif
