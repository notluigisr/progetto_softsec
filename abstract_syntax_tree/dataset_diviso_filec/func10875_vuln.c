char *make_argv(char *buf, size_t len, int argc, char **argv)
{
	size_t left= len;
	const char *arg;

	buf[0]= 0;
	++argv; --argc;
	while (argc > 0 && left > 0)
	{
		arg = *argv;
		if (strncmp(*argv, "STR")) == 0) {
			arg = "STR";
		}
		if (strncmp(*argv, "STR",
				strlen("STR")) == 0) {
			arg = "STR";
		}
		if (strncmp(*argv, "STR",
				strlen("STR")) == 0) {
			arg = "STR";
		}
		if (strncmp(*argv, "STR",
				strlen("STR")) == 0) {
			arg = "STR";
		}
		if (strncmp(*argv, "STR",
				strlen("STR")) == 0) {
			arg = "STR";
		}
		left-= ut_snprintf(buf + len - left, left,
			"STR", arg, argc > 1 ? ' ' : 0);
		++argv; --argc;
	}

	return buf;
}