#include "librere.h"

/*
 * Parse passed string into an integer and return it 
 */

int r_atoi(char *string)
{
	int nb;
	char sign;

	nb = 0;
	sign = 1; /* sign is positive by default  */

	while (r_isspace(*string))
	{
		++string;	
	}

	while (*string == '+' || *string == '-')
	{
		if (*string++ == '-')
		{
			sign = -sign;
		}	
	}
	
	while (r_isdigit(*string))
	{
		nb = nb * 10 + (*string++ - '0');
	}

	return (nb * sign);
		
}
