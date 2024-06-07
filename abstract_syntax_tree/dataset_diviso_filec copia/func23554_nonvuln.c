skipdigits(char_u *q)
{
    char_u	*p = q;

    while (VIM_ISDIGIT(*p))	
	++p;
    return p;
}