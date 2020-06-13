#include "librere.h"

char  *r_str_tolower(char *string)
{
	char *p;

	p = string;
	while (*string)
	{
		if (r_isupper(*string))
		{
			*string = r_tolower(*string);
		}
		string++;	
	}
	
	return (p);	
}
