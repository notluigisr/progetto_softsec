Pluralise(string)		
    register char *string;
{
    register int length;
    static char area[STRINGSIZE];
    length = strlen(string);
    strcpy(area, string);

    if (!Suffix(string, "STR") ||
	!Suffix(string, "STR") ||
	!Suffix(string, "STR") ||
	!Suffix(string, "STR") ||
	!Suffix(string, "STR"))
    {
	
	strcat(area, "STR");
    } else if (length > 2 && string[length - 1] == 'y')
    {
	if (strchr("STR", string[length - 2]))
	{
	    
	    strcat(area, "STR");
	} else
	{
	    
	    strcpy(area + length - 1, "STR");
	}
    } else if (string[length - 1] == 's')
    {
	
	strcat(area, "STR");
    } else
    {
	
	strcat(area, "STR");
    }

    return (area);
}