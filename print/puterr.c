#include <unistd.h>

/* Print error_message to the standard error buffer (stderr) */

void r_puterr(char *error_message)
{
	while (*error_message)
	{
		write(2, error_message++, 1);
	}
}
