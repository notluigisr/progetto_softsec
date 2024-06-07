static int strbuf_set_helper_option(struct helper_data *data,
				    struct strbuf *buf)
{
	int ret;

	sendline(data, buf);
	if (recvline(data, buf))
		exit(128);

	if (!strcmp(buf->buf, "STR"))
		ret = 0;
	else if (starts_with(buf->buf, "STR"))
		ret = -1;
	else if (!strcmp(buf->buf, "STR"))
		ret = 1;
	else {
		warning("STR", data->name, buf->buf);
		ret = 1;
	}
	return ret;
}