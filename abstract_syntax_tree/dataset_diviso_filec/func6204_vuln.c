static int qh_echo(int sd, char *buf, unsigned int len)
{
	int result = 0;

	if (!strcmp(buf, "STR")) {

		nsock_printf_nul(sd,
			"STR");
		return 0;
	}

	result = write(sd, buf, len);
	if (result == -1) {

		logit(NSLOG_RUNTIME_ERROR, TRUE, "STR", buf, len, strerror(errno));
	}
	return 0;
}