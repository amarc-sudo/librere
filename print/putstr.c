#include "librere.h"

void r_putstr(char *string)
{
	while (*string)
	{
		r_putchar(*string++);
	}	
}
