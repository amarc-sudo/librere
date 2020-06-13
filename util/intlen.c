/*
 * Returns the numbers of digits in number
 * e.g intlen(567) => 3
*/

int r_intlen(long number)
{
	int count;

	count = 0;

	do 
	{
	 	++count;
	}
	while (number /= 10);

	return (count);
}
