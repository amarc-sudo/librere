#include <unistd.h>
#include <stdio.h>

/*
 * print the passed integer in where output
 * standard output will likely be the most used, its identifier is 1 
*/

void r_put_int(int nb)
{

	if (nb < 0)
	{
		nb = -nb;
		write(1, "-", 1);	
	}

	if (nb >= 10)
	{
		r_put_int(nb / 10);
		r_put_int(nb % 10);
	}
	else
	{
		char digit;
		
		digit = nb + '0';
		write(1, &digit, 1);
	}
}
