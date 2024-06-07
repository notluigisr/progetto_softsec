smsg_attr(int attr, const char *s, ...)
{
    if (IObuff == NULL)
    {
	
	
	return msg_attr((char *)s, attr);
    }
    else
    {
	va_list arglist;

	va_start(arglist, s);
	vim_vsnprintf((char *)IObuff, IOSIZE, s, arglist);
	va_end(arglist);
	return msg_attr((char *)IObuff, attr);
    }
}