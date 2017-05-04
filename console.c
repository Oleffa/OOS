#include "include/stdarg.h"
#include "include/console.h"
#include "include/system.h"
#include <string.h>

int x = 5;
int y = 5;
unsigned short *video = (unsigned short*) 0xb8000;
int text = 0x0F;

void cursor(){
	unsigned temp;
	temp = y * 80 + x;
	outportb(0x3D4, 14);
	outportb(0x3D5, temp >> 8);
	outportb(0x3D4, 15);
	outportb(0x3D5, temp);
}
void kclear(){
	unsigned blank = 0x20 | (0x0F << 8);
	int t;
	for(t = 0; t < 2 * 25 * 80; t++){
		video[t] = blank;
	}
	x = y = 0;
	cursor();
}
void scroll(int lines){
	unsigned blank;

	blank = 0x20 | (text << 8);
	kmemcopy(video, video + lines * 80, (25 - lines) * 80 * 2);
	memset_short(video + (25 - lines) * 80, blank, 80);
	y = 25 - lines;
	x = 0;
}

void kprintchar(unsigned char c){
	unsigned short *where;
	unsigned att = text << 8;
	if(c == '\n'){
		x = 0;
		y++;
	}else if(c >= ' '){
		where = video + (y * 80 + x);
		*where = c | att;
		x++;
	}
	//go to next line when line is finished
	if(x >= 80){
		x = 0;
		y++;
	}
	if(y >= 25){
		scroll(1);
	}
	cursor();
}
void settextattributes(unsigned char text, unsigned char background){
	text = (background << 4) | (text & 0x0F);
}
void kprintf(const char *ch){
	while(*ch){
		kprintchar(*ch);
		ch++;
	}
	if(*ch != '\n'){
		kprintchar('\n');
	}
}
