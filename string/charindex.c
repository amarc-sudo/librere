/* Return the first index where a character is find in a string */
int r_charindex(char character, char *string)
{
	char *start_of_string = string;

	while (*start_of_string)
	{
		if (*start_of_string == character)
		{
			return (start_of_string - string);
		}	
		start_of_string++;
	}

	return (-1); /* No occurence of character in string */
}


