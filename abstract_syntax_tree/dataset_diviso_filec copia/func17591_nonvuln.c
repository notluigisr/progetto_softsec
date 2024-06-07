char *uwsgi_get_line(char *ptr, char *watermark, int *size) {
	char *p = ptr;
	int count = 0;

	while (p < watermark) {
		if (*p == '\n') {
			*size = count;
			return ptr + count;
		}
		count++;
		p++;
	}

	return NULL;
}