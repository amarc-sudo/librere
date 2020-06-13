/* 
 * Converts number to another base, which is specified by its entire charset
 * e.g itob(15, "0123456789ABCDEF") = > "F"
*/
#include "librere.h"
#include <stdlib.h>

char *r_itob(int number, char *base_charset)
{
	unsigned base_length, intlen;
	char *string;
	char is_negative;

	is_negative = 0;
	if (number < 0)
	{
		is_negative = 1;
		number = -number;
	}
	
	base_length = r_strlen(base_charset);
	intlen = r_intbaselen(number, base_length);	
	string = malloc(intlen + is_negative + 1);

	do
	{
		*string++ = base_charset[number % base_length];
	}
	while (number /= base_length);

	if (is_negative)
	{
		*string++ = '-';
	}
	*string = '\0';

	return (r_str_reverse(string - (intlen + is_negative)));
}

