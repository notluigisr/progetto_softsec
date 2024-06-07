u32 gf_utf8_mbstowcs(unsigned short* dest, size_t len, const char** srcp)
{
	gf_utf8_mbstate_t* ps = &internal;
	const char *src = *srcp;

	unsigned short* destptr = dest;
	for (; len > 0; destptr++, len--) {
		const char* backup_src = src;
		unsigned char c;
		unsigned short wc;
		size_t count;
		if (ps->count == 0) {
			c = (unsigned char) *src;
			if (c < 0x80) {
				*destptr = (wchar_t) c;
				if (c == 0) {
					src = NULL;
					break;
				}
				src++;
				continue;
			} else if (c < 0xC0) {
				
				goto bad_input;
			}
			if (c < 0xE0) {
				wc = (wchar_t)(c & 0x1F) << 6;
				count = 1;
				if (c < 0xC2) goto bad_input;
			} else if (c < 0xF0) {
				wc = (wchar_t)(c & 0x0F) << 12;
				count = 2;
			}
			else goto bad_input;
			src++;
		} else {
			wc = ps->value << 6;
			count = ps->count;
		}
		for (;;) {
			c = (unsigned char) *src++ ^ 0x80;
			if (!(c < 0x40)) goto bad_input_backup;
			wc |= (unsigned short) c << (6 * --count);
			if (count == 0)
				break;
			
			if ((unsigned short) wc < ((unsigned short) 1 << (5 * count + 6)))
				goto bad_input_backup;
		}
		*destptr = wc;
		ps->count = 0;
		continue;

bad_input_backup:
		src = backup_src;
		goto bad_input;
	}
	*srcp = src;
	return (u32) (destptr - dest);

bad_input:
	*srcp = src;
	return GF_UTF8_FAIL;
}