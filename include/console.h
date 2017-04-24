#include <inttypes.h>
#ifndef CONSOLE_H
#define CONSOLE_H

void kclear(void);
void kprintf(const char* c);
void scrollUP(int lines);
#endif
