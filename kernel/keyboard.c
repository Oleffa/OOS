#include "include/system.h"
#include "include/console.h"
#include "osl/osl.h"
/* Contains keymap */
unsigned char keymap[128];


/* Handler for Keyboard iterrupts */
void keyboard_handler(struct regs *r) {
	unsigned char scancode;

	/* Read from keyboard data buffer */
	scancode = inportb(0x60);

	if (scancode & 0x80) {
		/* Code for shift, alt, ctrl can go here*/
	} else {
		switch (keymap[scancode])
		{	
			case 'c':
				k_cls();
				break;
			case 'h':
				k_printf(HELP_MESSAGE);
				break;
			case 'v':
				IDLE_OUTPUT = !IDLE_OUTPUT;
				break;
			case 'u':
				k_printf("Uptime: ");
				int t = 2;
				k_printf(int_to_chararray(t, 10));
				k_printf("\n");
				break;
			case 'i':
				__asm__ __volatile__ ("int $0");
				break;
			default:
				k_putch(keymap[scancode], -1, -1);
				break;
		}
	}
}

/* Init keymap and install IRQ handler in irq.c*/
void keyboard_install() {
	keymap[0] = 0;
	keymap[1] = 27;
	keymap[2] = '1';
	keymap[3] = '2';
	keymap[4] = '3';
	keymap[5] = '4';
	keymap[6] = '5';
	keymap[7] = '6';
	keymap[8] = '7';
	keymap[9] = '8'; 
	keymap[10] = '9';
	keymap[11] = '0';
	keymap[12] = '-';
	keymap[13] = '=';
	keymap[14] = '\b';	/* Backspace */
	keymap[15] = '\t';	/* Tab */
	keymap[16] = 'q';
	keymap[17] = 'w';
	keymap[18] = 'e';
	keymap[19] = 'r'; 	/* 19 */
	keymap[20] = 't';
	keymap[21] = 'y';
	keymap[22] = 'u';
	keymap[23] = 'i';
	keymap[24] = 'o';
	keymap[25] = 'p';
	keymap[26] = '[';
	keymap[27] = ']';
	keymap[28] = '\n'; 	/* Enter key */
	keymap[29] = 0;    	/* Control */
	keymap[30] = 'a';
	keymap[31] = 's';
	keymap[32] = 'd';
	keymap[33] = 'f';
	keymap[34] = 'g';
	keymap[35] = 'h';
	keymap[36] = 'j';
	keymap[37] = 'k';
	keymap[38] = 'l';
	keymap[39] = ';'; 	/* 39 */
	keymap[40] = '\'';
	keymap[41] = '`';
	keymap[42] = 0; 	/* Left shift */
	keymap[43] = '\\';
	keymap[44] = 'z';
	keymap[45] = 'x';
	keymap[46] = 'c';
	keymap[47] = 'v';
	keymap[48] = 'b';
	keymap[49] = 'n'; 	/* 49 */
	keymap[50] = 'm';
	keymap[51] = ',';
	keymap[52] = '.';
	keymap[53] = '/';
	keymap[54] = 0; 	/* Right shift */
	keymap[55] = '*';
	keymap[56] = 0;   	/* Alt */
	keymap[57] = ' '; 	/* Space bar */
	keymap[58] = 0;   	/* Caps lock */
	keymap[59] = 0;  	/* 59 - F1 key ... > */
	keymap[60] = 0;
	keymap[61] = 0;
	keymap[62] = 0;
	keymap[63] = 0;
	keymap[64] = 0;
	keymap[65] = 0;
	keymap[66] = 0;
	keymap[67] = 0;
	keymap[68] = 0; 	/* < ... F10 */
	keymap[69] = 0; 	/* 69 - Num lock*/
	keymap[70] = 0; 	/* Scroll Lock */
	keymap[71] = 0; 	/* Home key */
	keymap[72] = 0; 	/* Up Arrow */
	keymap[73] = 0; 	/* Page Up */
	keymap[74] = '-';
	keymap[75] = 0; 	/* Left Arrow */
	keymap[76] = 0;
	keymap[77] = 0; 	/* Right Arrow */
	keymap[78] = '+';
	keymap[79] = 0; 	/* 79 - End key*/
	keymap[80] = 0; 	/* Down Arrow */
	keymap[81] = 0; 	/* Page Down */
	keymap[82] = 0; 	/* Insert Key */
	keymap[83] = 0; 	/* Delete Key */
	keymap[84] = 0;
	keymap[85] = 0;
	keymap[86] = 0;
	keymap[87] = 0; 	/* F11 Key */
	keymap[88] = 0; 	/* F12 Key */
	keymap[89] = 0; 	/* All other keys are undefined */

	irq_install_handler(1, keyboard_handler);
}
