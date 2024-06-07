static int get_name(int counter,
		unsigned char *pkt, unsigned char *start, unsigned char *max,
		unsigned char *output, int output_max, int *output_len,
		unsigned char **end, char *name, int *name_len)
{
	unsigned char *p;

	
	if (counter > 10)
		return -EINVAL;

	p = start;
	while (*p) {
		if ((*p & NS_CMPRSFLGS) == NS_CMPRSFLGS) {
			uint16_t offset = (*p & 0x3F) * 256 + *(p + 1);

			if (offset >= max - pkt)
				return -ENOBUFS;

			if (!*end)
				*end = p + 2;

			return get_name(counter + 1, pkt, pkt + offset, max,
					output, output_max, output_len, end,
					name, name_len);
		} else {
			unsigned label_len = *p;

			if (pkt + label_len > max)
				return -ENOBUFS;

			if (*output_len > output_max)
				return -ENOBUFS;

			
			name[(*name_len)++] = label_len;
			memcpy(name + *name_len, p + 1,	label_len + 1);
			*name_len += label_len;

			
			output[0] = NS_CMPRSFLGS;
			output[1] = 0x0C;
			*output_len = 2;

			p += label_len + 1;

			if (!*end)
				*end = p;

			if (p >= max)
				return -ENOBUFS;
		}
	}

	return 0;
}