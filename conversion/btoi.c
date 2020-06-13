/* 
	Converts string in a given base into its decimal form
*/
#include "librere.h"
#include <stdio.h>

int r_btoi(char *string, char *base_charset)
{
	unsigned base_length;
	int number, charindex;
	char sign;

	base_length = r_strlen(base_charset);
	number = 0;
	sign = 1;

	while (r_isspace(*string))
	{
		string++;
	}
	while (*string == '+' || *string == '-')
	{
		if (*string++ == '-')
		{
			sign = -sign;
		}
	}
	
	while ((charindex = r_charindex(*string++, base_charset)) != -1)
	{
		number = number * base_length + charindex;
	}
	
	return (number * sign);		
}
