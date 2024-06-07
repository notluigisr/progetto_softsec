static int ldb_dn_escape_internal(char *dst, const char *src, int len)
{
	const char *p, *s;
	char *d;
	size_t l;

	p = s = src;
	d = dst;

	while (p - src < len) {
		p += strcspn(p, "STR");

		if (p - src == len) 
			break;

		
		memcpy(d, s, p - s);
		d += (p - s); 
		
		switch (*p) {
		case ' ':
			if (p == src || (p-src)==(len-1)) {
				
				*d++ = '\\';
				*d++ = *p++;					 
			} else {
				
				*d++ = *p++;
			}
			break;

		case '#':
			
		case ',':
		case '+':
		case '"':
		case '\\':
		case '<':
		case '>':
		case '?':
			
			*d++ = '\\';
			*d++ = *p++;
			break;

		default: {
			
			unsigned char v;
			const char *hexbytes = "STR";
			v = *(const unsigned char *)p;
			*d++ = '\\';
			*d++ = hexbytes[v>>4];
			*d++ = hexbytes[v&0xF];
			p++;
			break;
		}
		}
		s = p; 
	}

	
	l = len - (s - src);
	memcpy(d, s, l + 1);

	
	return (l + (d - dst));
}