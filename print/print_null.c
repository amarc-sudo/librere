#include <stdio.h>

void	r_print_null(char *str)
{
	while (*str)
	{
		putchar(*str++);
	}
	while (*str++ == '\0')
	{
		printf("\\0");
	}
}
