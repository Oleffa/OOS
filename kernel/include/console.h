#ifndef CONSOLE_H
#define CONSOLE_H

// Define size of the terminal (depends the VGA controller)
#define MAX_COLS 80
#define MAX_ROWS 25

// Define the CRT register of the VGA controller
#define REG_SCREEN_CTRL 0x3D4
// Define the DATA register of the VGA controller
#define REG_SCREEN_DATA 0x3D5

// Define the color palette
#define BLACK 	0x0
#define BLUE 	0x1
#define GREEN 	0x2
#define CYAN 	0x3
#define RED	0x4
#define MAGENTA	0x5
#define BROWN	0x6
#define LIGHT_GREY	0x7
#define DARK_GREY	0x8
#define LIGHT_BLUE	0x9
#define LIGHT_GREEN	0xA
#define LIGHT_CYAN	0xB
#define LIGHT_RED	0xC
#define LIGHT_MAGENTA	0xD
#define LIGHT_BROWN	0xE
#define WHITE 	0xF

/* Kernel console functions */
extern int k_get_csr();
extern int k_get_screen_offset(int row, int col);
extern void k_set_csr(int offset);
extern void k_cls();
extern void k_print_at(char* message, int row, int col);
extern int k_scroll(int offset);
extern void k_putch(char c, int row, int col);
extern void k_printf(unsigned char *text);
extern void k_change_text_att(unsigned char forecolor, unsigned char backcolor);
extern void k_set_color_scheme(int scheme);
/* Init kernel console, called in kernel.c */
extern void init_video(void);
#endif
