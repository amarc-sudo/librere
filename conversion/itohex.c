/*
 * Converts a numeric value  into it's 
 * hexadecimal representation (as a string) 
*/

#include "librere.h"
#include <stdlib.h>

char *r_itohex(long number)
{
		char charset[] =
		{
			'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
			'A', 'B', 'C', 'D', 'E', 'F'
		};

		char *start_of_string;
		char *hex_string;
		int intlen;
		char is_negative;

		is_negative = 0;
		intlen = r_intlen(number);	

		if (number < 0)
		{
			number = -number;
			is_negative = 1;
		}

		hex_string = (char *) malloc(intlen + is_negative + 1);
		start_of_string = hex_string;

		do
		{
			*start_of_string++ = charset[number % 16];  
		}
		while (number /= 16);
	
		if (is_negative)
		{
			*start_of_string++ = '-';
		}

		*start_of_string = '\0';

		return (r_str_reverse(hex_string));
}



