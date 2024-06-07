static int http_del_hdr_value(char *start, char *end, char **from, char *next)
{
	char *prev = *from;

	if (prev == start) {
		
		if (next < end)
			next++;

		while (next < end && HTTP_IS_SPHT(*next))
			next++;
	}
	else {
		
		while (HTTP_IS_SPHT(*(prev-1)))
			prev--;
		*from = prev;

		
		if (next < end) {
			*prev++ = *next++;
			if (prev + 1 < next)
				*prev++ = ' ';
			while (next < end && HTTP_IS_SPHT(*next))
				next++;
		}
	}
	memmove(prev, next, end - next);
	return (prev - next);
}