tabstop_set(char_u *var, int **array)
{
    int valcount = 1;
    int t;
    char_u *cp;

    if (var[0] == NUL || (var[0] == '0' && var[1] == NUL))
    {
	*array = NULL;
	return TRUE;
    }

    for (cp = var; *cp != NUL; ++cp)
    {
	if (cp == var || cp[-1] == ',')
	{
	    char_u *end;

	    if (strtol((char *)cp, (char **)&end, 10) <= 0)
	    {
		if (cp != end)
		    emsg(_(e_positive));
		else
		    emsg(_(e_invarg));
		return FALSE;
	    }
	}

	if (VIM_ISDIGIT(*cp))
	    continue;
	if (cp[0] == ',' && cp > var && cp[-1] != ',' && cp[1] != NUL)
	{
	    ++valcount;
	    continue;
	}
	emsg(_(e_invarg));
	return FALSE;
    }

    *array = ALLOC_MULT(int, valcount + 1);
    if (*array == NULL)
	return FALSE;
    (*array)[0] = valcount;

    t = 1;
    for (cp = var; *cp != NUL;)
    {
	(*array)[t++] = atoi((char *)cp);
	while (*cp  != NUL && *cp != ',')
	    ++cp;
	if (*cp != NUL)
	    ++cp;
    }

    return TRUE;
}