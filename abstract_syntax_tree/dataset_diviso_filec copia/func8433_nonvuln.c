utf_safe_read_char_adv(char_u **s, size_t *n)
{
    int		c, k;

    if (*n == 0) 
	return 0;

    k = utf8len_tab_zero[**s];

    if (k == 1)
    {
	
	(*n)--;
	return *(*s)++;
    }

    if ((size_t)k <= *n)
    {
	
	
	
	c = utf_ptr2char(*s);

	
	
	
	
	
	if (c != (int)(**s) || (c == 0xC3 && (*s)[1] == 0x83))
	{
	    
	    *s += k;
	    *n -= k;
	    return c;
	}
    }

    
    return -1;
}