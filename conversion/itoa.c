#include <stdlib.h>
#include <stdio.h>
#include "librere.h"

char *r_itoa(int number)
{
	unsigned intlen, i;
	char is_negative;
	char *string;

	intlen = r_intlen(number);
	i = 0;
	is_negative = 0;
	
	if (number < 0)
	{
		is_negative = 1;
		number = -number;
	}

	/* 
	  * Allocates memory for string. is_negative will add 1 byte of storage
	  * if number is negative, granting enough space for the minus sign.	
	 */
	string = (char *)malloc(intlen + is_negative + 1);	

	do 
	{
	 	string[i++] = number % 10 + '0';
	}	
	while (number /= 10);

	if (is_negative)
	{
		string[i++] = '-';
	}
	string[i] = '\0';
	r_str_reverse(string);

	return (string);
}

