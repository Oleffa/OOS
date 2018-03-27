#include "osl.h"
#include <stdbool.h>

int strlen(const char *str)
{
	int i;
	for (i = 0; *str != '\0'; str++){i++;}
	return i;
}

void invert_string(char str[])
{
	int start, end;
	char temp;
	for (start = 0 ,end = strlen(str) - 1; start < end; start++, end--)
	{
		temp = *(str+start);
		*(str+start) = *(str+end);
		*(str+end) = temp;
	}
}

/* convert an integer to a char based on the base */
char* int_to_chararray(int in, int base)
{
	char str[128];
	int i = 0;
        /* Check if the number in question is negative or not */
        bool negative = false;  
        if (in < 0)
        {       
                negative = true;
                in = -in;
        }
        while (in != 0)
        {
                int rest = in % base;
                str[i++] = (rest > 9) ? (rest - 10) + 'A' : rest + '0';
                in = in / base;
        }
        /* Append - for negative numbers */
        if (negative){str[i++] = '-';}
        str[i] = '\0';
	invert_string(str);
        return str;
}

