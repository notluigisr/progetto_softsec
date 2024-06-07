skiptodigit(char_u *q)
{
    char_u	*p = q;

    while (*p != NUL && !VIM_ISDIGIT(*p))	
	++p;
    return p;
}