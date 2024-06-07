tabstop_set(char_u *var, int **array)
{
    int	    valcount = 1;
    int	    t;
    char_u  *cp;

    if (var[0] == NUL || (var[0] == '0' && var[1] == NUL))
    {
	*array = NULL;
	return OK;
    }

    for (cp = var; *cp != NUL; ++cp)
    {
	if (cp == var || cp[-1] == ',')
	{
	    char_u *end;

	    if (strtol((char *)cp, (char **)&end, 10) <= 0)
	    {
		if (cp != end)
		    emsg(_(e_argument_must_be_positive));
		else
		    semsg(_(e_invalid_argument_str), cp);
		return FAIL;
	    }
	}

	if (VIM_ISDIGIT(*cp))
	    continue;
	if (cp[0] == ',' && cp > var && cp[-1] != ',' && cp[1] != NUL)
	{
	    ++valcount;
	    continue;
	}
	semsg(_(e_invalid_argument_str), var);
	return FAIL;
    }

    *array = ALLOC_MULT(int, valcount + 1);
    if (*array == NULL)
	return FAIL;
    (*array)[0] = valcount;

    t = 1;
    for (cp = var; *cp != NUL;)
    {
	int n = atoi((char *)cp);

	
	if (n < 0 || n > TABSTOP_MAX)
	{
	    semsg(_(e_invalid_argument_str), cp);
	    vim_free(*array);
	    *array = NULL;
	    return FAIL;
	}
	(*array)[t++] = n;
	while (*cp != NUL && *cp != ',')
	    ++cp;
	if (*cp != NUL)
	    ++cp;
    }

    return OK;
}