#include "include/stdarg.h"
#include "include/console.h"

static int x = 0;
static int y = 0;
char* video = (char*) 0xb8000;
uint8_t color = 0x1;

void kclear(void){
	int t;
	for (t = 0; t < 2 * 25 * 80; t++) {
		video[t] = 0;
	}
	x = y = 0;
}
static void kprintchar(uint8_t c, uint8_t color, uint8_t x, uint8_t y){
	//calculate adress
	uint16_t* off = (uint16_t*)0xB8000;
	off += y * 80 + x;
	*off = (((uint16_t)color) << 8) | c;
}
//static void kprintchar_16(uint16_t symbol, uint8_t x, uint8_t y){
//	uint16_t* off = (uint16_t*)0xB8000;
//	off += y * 80 + x;
//	*off = symbol;
//}
static char getChar(uint8_t x, uint8_t y){
	uint16_t off = (uint16_t)0xB8000;
	char ret;
	off += y * 80 + x;
	off *= 2;
	ret = (char)(off & 0xFF);
	return ret;
}
void scrollUP(int lines){
	int z;
	int u;
	int v;
	for(z = 0; z < 25; z++){
		for(u = 0; u < 80; u++){
			kprintchar(getChar(u,z+1), color, u, z);
		}
	}
	for(v = 0; v < 80; v++){
		kprintchar(' ', color, v, 24);
	}
}
static void updateXY(int x_update, int y_update){
//	uint16_t tmp;
	//updating the position of the cursor and going into next line or scroll mode
	x = x + x_update;
	y = y + y_update;
	if(x >= 80){
		x = 0;
		y = y + 1;
	}
	if(y >= 25){
		y = 24;
		scrollUP(1);
	}
	//display the cursor
	//TODO
	//tmp = y * 25 * x;
	//outb(0x3D4,14);
	//outb(0x3D5,tmp >> 8);
//	outb(0x3D4,15);
//	outb(0x3D5,tmp);
}
void kprintf(const char* ch){
	while(*ch){
		kprintchar(*ch, color, x, 10);
		updateXY(1,0);
		ch++;
	}
}
