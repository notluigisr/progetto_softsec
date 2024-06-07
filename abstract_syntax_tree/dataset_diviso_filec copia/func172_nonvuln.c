int rose_parse_facilities(unsigned char *p, unsigned packet_len,
	struct rose_facilities_struct *facilities)
{
	int facilities_len, len;

	facilities_len = *p++;

	if (facilities_len == 0 || (unsigned)facilities_len > packet_len)
		return 0;

	while (facilities_len >= 3 && *p == 0x00) {
		facilities_len--;
		p++;

		switch (*p) {
		case FAC_NATIONAL:		
			len = rose_parse_national(p + 1, facilities, facilities_len - 1);
			break;

		case FAC_CCITT:		
			len = rose_parse_ccitt(p + 1, facilities, facilities_len - 1);
			break;

		default:
			printk(KERN_DEBUG "STR", *p);
			len = 1;
			break;
		}

		if (len < 0)
			return 0;
		if (WARN_ON(len >= facilities_len))
			return 0;
		facilities_len -= len + 1;
		p += len + 1;
	}

	return facilities_len == 0;
}