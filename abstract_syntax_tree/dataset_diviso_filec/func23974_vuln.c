cstrchr(char_u *s, int c)
{
    char_u	*p;
    int		cc;

    if (!rex.reg_ic || (!enc_utf8 && mb_char2len(c) > 1))
	return vim_strchr(s, c);

    
    
    
    if (enc_utf8 && c > 0x80)
	cc = utf_fold(c);
    else
	 if (MB_ISUPPER(c))
	cc = MB_TOLOWER(c);
    else if (MB_ISLOWER(c))
	cc = MB_TOUPPER(c);
    else
	return vim_strchr(s, c);

    if (has_mbyte)
    {
	for (p = s; *p != NUL; p += (*mb_ptr2len)(p))
	{
	    if (enc_utf8 && c > 0x80)
	    {
		if (utf_fold(utf_ptr2char(p)) == cc)
		    return p;
	    }
	    else if (*p == c || *p == cc)
		return p;
	}
    }
    else
	
	for (p = s; *p != NUL; ++p)
	    if (*p == c || *p == cc)
		return p;

    return NULL;
}