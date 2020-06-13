#include <unistd.h>
#include "librere.h"

int r_putchar(char c)
{
	if (c >= 0)
	{
		write(1, &c, 1);
		return (1);
	}
		
	return (0);
}

