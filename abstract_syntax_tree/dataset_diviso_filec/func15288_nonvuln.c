static size_t srs(struct jtype j[], uint8_t *ptr)
{
	size_t l, len = 0;

	while(j->jobj) {
		l = sr(j, ptr);
		if (!l)
			return 0;
		len += l;
		if (ptr)
			ptr += l;
		j++;
	}
	return len;
}