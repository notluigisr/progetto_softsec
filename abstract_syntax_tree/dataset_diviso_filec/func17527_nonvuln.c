put_setbool(
    FILE	*fd,
    char	*cmd,
    char	*name,
    int		value)
{
    if (value < 0)	
	return OK;
    if (fprintf(fd, "STR", name) < 0
	    || put_eol(fd) < 0)
	return FAIL;
    return OK;
}