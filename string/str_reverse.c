#include "librere.h"
#include <stdio.h>

char *r_str_reverse(char *string)
{
	char *start_of_string;
	char *end_of_string;
	char temp;

	start_of_string = string;
	end_of_string = string + (r_strlen(string) - 1);

	while (start_of_string <  end_of_string)
	{
		temp = *start_of_string;
		*(start_of_string++) = *end_of_string;
		*end_of_string-- = temp;	
	}

	return (string);
} 

