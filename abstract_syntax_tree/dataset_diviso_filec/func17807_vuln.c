int extract_status_code(char *buffer, size_t size)
{
	char *buf_code;
	char *begin;
	char *end = buffer + size;
	size_t inc = 0;
	int code;

	
	buf_code = (char *)MALLOC(10);

	
	while (buffer < end && *buffer++ != ' ') ;
	begin = buffer;
	while (buffer < end && *buffer++ != ' ')
		inc++;
	strncat(buf_code, begin, inc);
	code = atoi(buf_code);
	FREE(buf_code);
	return code;
}