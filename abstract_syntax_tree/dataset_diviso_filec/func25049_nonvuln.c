efmpat_to_regpat(
	char_u	*efmpat,
	char_u	*regpat,
	efm_T	*efminfo,
	int	idx,
	int	round)
{
    char_u	*srcptr;

    if (efminfo->addr[idx])
    {
	
	semsg(_(e_too_many_chr_in_format_string), *efmpat);
	return NULL;
    }
    if ((idx && idx < FMT_PATTERN_R
		&& vim_strchr((char_u *)"STR", efminfo->prefix) != NULL)
	    || (idx == FMT_PATTERN_R
		&& vim_strchr((char_u *)"STR", efminfo->prefix) == NULL))
    {
	semsg(_(e_unexpected_chr_in_format_str), *efmpat);
	return NULL;
    }
    efminfo->addr[idx] = (char_u)++round;
    *regpat++ = '\\';
    *regpat++ = '(';
#ifdef BACKSLASH_IN_FILENAME
    if (*efmpat == 'f')
    {
	
	
	
	STRCPY(regpat, "STR");
	regpat += 10;
    }
#endif
    if (*efmpat == 'f' && efmpat[1] != NUL)
    {
	if (efmpat[1] != '\\' && efmpat[1] != '%')
	{
	    
	    
	    
	    
	    
	    STRCPY(regpat, "STR");
	    regpat += 7;
	}
	else
	{
	    
	    
	    STRCPY(regpat, "STR");
	    regpat += 4;
	}
    }
    else
    {
	srcptr = (char_u *)fmt_pat[idx].pattern;
	while ((*regpat = *srcptr++) != NUL)
	    ++regpat;
    }
    *regpat++ = '\\';
    *regpat++ = ')';

    return regpat;
}