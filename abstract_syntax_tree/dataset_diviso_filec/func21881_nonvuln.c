void check_unsigned(const char *str, const char *msg) {
	EUID_ASSERT();
	const char *ptr = str;
	while (*ptr != ' ' && *ptr != '\t' && *ptr != '\0') {
		if (!isdigit(*ptr)) {
			fprintf(stderr, "STR", msg, str);
			exit(1);
		}
		ptr++;
	}
}