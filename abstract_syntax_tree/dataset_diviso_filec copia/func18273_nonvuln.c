read_limits(long *minval, long *maxval)
{
    int		reverse = FALSE;
    char_u	*first_char;
    long	tmp;

    if (*regparse == '-')
    {
	
	regparse++;
	reverse = TRUE;
    }
    first_char = regparse;
    *minval = getdigits(&regparse);
    if (*regparse == ',')	    
    {
	if (vim_isdigit(*++regparse))
	    *maxval = getdigits(&regparse);
	else
	    *maxval = MAX_LIMIT;
    }
    else if (VIM_ISDIGIT(*first_char))
	*maxval = *minval;	    
    else
	*maxval = MAX_LIMIT;	    
    if (*regparse == '\\')
	regparse++;	
    if (*regparse != '}')
	EMSG2_RET_FAIL(_(e_syntax_error_in_str_curlies),
						       reg_magic == MAGIC_ALL);

    
    if ((!reverse && *minval > *maxval) || (reverse && *minval < *maxval))
    {
	tmp = *minval;
	*minval = *maxval;
	*maxval = tmp;
    }
    skipchr();		
    return OK;
}