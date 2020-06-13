int r_strlen(char *string)
{
	char *p = string;
	
	while (*p++)
		;

	return (--p - string); /* pointer has gone one too far */
}
