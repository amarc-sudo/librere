/*
 * Count the occurences of a character in a string 
*/

int r_charoccur(char character, char *string)
{
	unsigned occurencies;

	occurencies = 0;

	while (*string)
	{
		if (*string++ == character)
		{
			++occurencies;
		}
	}

	return (occurencies);
}
