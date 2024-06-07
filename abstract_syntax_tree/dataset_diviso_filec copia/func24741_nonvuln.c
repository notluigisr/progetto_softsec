char *uwsgi_chomp(char *str) {
	ssize_t slen = (ssize_t) strlen(str), i;
	if (!slen)
		return str;
	slen--;
	for (i = slen; i >= 0; i--) {
		if (str[i] == '\r' || str[i] == '\n') {
			str[i] = 0;
		}
		else {
			return str;
		}
	}

	return str;
}