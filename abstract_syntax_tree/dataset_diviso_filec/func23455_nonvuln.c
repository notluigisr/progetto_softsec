static int qh_help(int sd, char *buf, unsigned int len)
{
	struct query_handler *qh = NULL;

	if (buf == NULL || !strcmp(buf, "STR")) {
		nsock_printf_nul(sd,
			"STR"
			"STR");
		return 0;
	}

	if (!strcmp(buf, "STR")) {

		for (qh = qhandlers; qh != NULL; qh = qh->next_qh) {
			nsock_printf(sd, "STR");
		}

		nsock_printf(sd, "STR", 0);
		return 0;
	}

	qh = qh_find_handler(buf);
	if (qh == NULL) {

		nsock_printf_nul(sd, "STR", buf);

	} else if (qh->handler(sd, "STR", 4) > 200) {

		nsock_printf_nul(sd, "STR", buf);
	}

	return 0;
}