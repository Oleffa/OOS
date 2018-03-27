#include "include/system.h"	// Kernel functions
#include "include/console.h"	// External function declarations

/* Upper 8 bits containing information about foreground and background color of the current character*/
char text_attribute;
/* Text memory buffer located at 0xB8000*/
unsigned char* video;

/* Calculates the position of an row|col coordinate on the 80x25 kernel terminal in text memory buffer */
int k_get_screen_offset(int row, int col)
{
	return(row * MAX_COLS + col) * 2;
}

/* Returns the cursor position in offset */
int k_get_csr()
{
	outportb(REG_SCREEN_CTRL, 14);
	int offset = inportb(REG_SCREEN_DATA) << 8;
	outportb(REG_SCREEN_CTRL, 15);
	offset += inportb(REG_SCREEN_DATA);
	return offset * 2;
}

/* Update the hardware cursor to a specific position in the text memory buffer */
void k_set_csr(int offset)
{
	offset /=2;
	outportb(REG_SCREEN_CTRL, 14);
	outportb(REG_SCREEN_DATA, (unsigned char)(offset >> 8));
	outportb(REG_SCREEN_CTRL, 15);
	outportb(REG_SCREEN_DATA, (unsigned char)(offset));
}

/* Clears the screen by printing ' ' everywhere */
void k_cls()
{
	int i,j;
	for (i = 0; i < MAX_ROWS; i++)
	{
		for (j = 0; j < MAX_COLS; j++)
		{
			k_putch(' ', i, j);	
		}
	}
	/* Reset the cursor position to 0, 0 */
	k_set_csr(k_get_screen_offset(0,0));
}

/* Prints a string/array of chars at the specified position */
void k_print_at(char* message, int row, int col)
{
	/* Set position of the cursor */
	if (row >= 0 && col >= 0)
	{
		k_set_csr(k_get_screen_offset(row,col));
	}
	/* Output the chars of the string, basically the same as the k_printf function*/
	char c;
	int i = 0;
	while ((c = message[i++]) != 0)
	{
		k_putch(c, -1, -1);
	}
}

/* Scroll the content of the screen down for 1 row if necessary */
int k_scroll(int offset)
{
	/* Return the current offset position if it is still in the 80x25 output window */
	if (offset < MAX_ROWS * MAX_COLS * 2)
	{
		return offset;
	}
	/* Put every char/attribute one line higher in the text memory buffer using the offset function */	
	int i, j;
	char *c, *cc;
	for (i = 1; i < MAX_ROWS; i++){
		for (j = 0; j < MAX_COLS; j++){
			video[k_get_screen_offset(i-1,j)] = video[k_get_screen_offset(i,j)];
		}
	}
	/* Empty the last line as it will be the new empty line to type in */
	for (j = 0; j < MAX_COLS * 2; j++)
	{
		video[k_get_screen_offset(MAX_ROWS-1,j)] = 0;
	}
	/* Update offset of the current output position after scrolling (first column in the last row usually)*/
	offset = k_get_screen_offset(MAX_ROWS-1,0);
	return offset;
}

/* Puts a single character on the screen at a row|col position in the 80x25 kernel console */
void k_putch(char c, int row, int col)
{
	/* Set textattribute to standard if there is none set */
	if(!text_attribute)
	{
		k_change_text_att(BLACK, WHITE);
	}
	/* Set the offset of the position where the char should be printed */
	int offset;
	/* Catch the case when the cursor is not on the screeen */
	if (row >= 0 && col >= 0)
	{
		offset = k_get_screen_offset(row, col);
	}else{
		offset = k_get_csr();
	}
	/* If the char is '\n' increase the row count to add a new line */	
	int rows;
	switch(c){
		case '\n':
			rows = offset / (2*MAX_COLS);
			offset = k_get_screen_offset(rows,79);
			break;
		default:
			video[offset] = c;
			video[offset+1] = text_attribute;
	}
	/* Scroll if necessary */
	offset = k_scroll(offset+2);
	/* Set the cursor position to the position after the char has been written */
	k_set_csr(offset);
}

/* Print a string to the kernel console using the putchar method for an array of chars/string */
void k_printf(unsigned char *text)
{
    int i;
    for (i = 0; text[i]!='\0'; i++)
    {
        k_putch(text[i], -1, -1);
    }
}

/* Set text attribute using the attribute byte (upper 8 bits of the text memory buffer)*/
void k_change_text_att(unsigned char forecolor, unsigned char backcolor)
{
    text_attribute = (backcolor << 4) | (forecolor & 0x0F);
}

/* Set color scheme for the kernel console by changing the text attribute that determines the back and foreground color*/
void k_set_color_scheme(int scheme)
{
	switch(scheme)
	{
		case 0://White on Black
			k_change_text_att(WHITE, BLACK);
			break;
		case 1://Black on White
			k_change_text_att(BLACK, WHITE);
			break;
		case 2://Vintage
			k_change_text_att(LIGHT_RED, LIGHT_CYAN);
			break;
		case 3:
			k_change_text_att(RED, LIGHT_GREEN);
			break;
		default:
			k_change_text_att(WHITE, BLACK);
	}
	k_cls();
}

/* Initialize video controller */
void init_video(void)
{
    // Set text memory buffer address
    video = (unsigned char*) 0xb8000;
    //init text to be black on white
    k_change_text_att(WHITE, BLACK);
    //clear initial boot messages
    k_cls();
}
