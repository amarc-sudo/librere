int r_intbaselen(long number, int base)
{
	int count;

	count = 0;
	do 
	{
		++count;
	}
	while (number /= base);

	return (count);
}
