pg_vfprintf(FILE *stream, const char *fmt, va_list args)
{
	PrintfTarget target;
	char		buffer[1024];	

	if (stream == NULL)
	{
		errno = EINVAL;
		return -1;
	}
	target.bufstart = target.bufptr = buffer;
	target.bufend = buffer + sizeof(buffer) - 1;
	target.stream = stream;
	target.nchars = 0;
	if (dopr(&target, fmt, args))
	{
		errno = EINVAL;			
		return -1;
	}
	
	flushbuffer(&target);
	return target.nchars;
}