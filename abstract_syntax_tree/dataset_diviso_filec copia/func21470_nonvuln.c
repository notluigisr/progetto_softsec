int gg_send_packet(struct gg_session *sess, int type, ...)
{
	struct gg_header *h;
	char *tmp;
	unsigned int tmp_length;
	void *payload;
	unsigned int payload_length;
	va_list ap;
	int res;

	gg_debug_session(sess, GG_DEBUG_FUNCTION, "STR", sess, type);

	tmp_length = sizeof(struct gg_header);

	if (!(tmp = malloc(tmp_length))) {
		gg_debug_session(sess, GG_DEBUG_ERROR, "STR");
		return -1;
	}

	va_start(ap, type);

	payload = va_arg(ap, void *);

	while (payload) {
		char *tmp2;

		payload_length = va_arg(ap, unsigned int);

		if (!(tmp2 = realloc(tmp, tmp_length + payload_length))) {
			gg_debug_session(sess, GG_DEBUG_ERROR, "STR");
			free(tmp);
			va_end(ap);
			return -1;
		}

		tmp = tmp2;

		memcpy(tmp + tmp_length, payload, payload_length);
		tmp_length += payload_length;

		payload = va_arg(ap, void *);
	}

	va_end(ap);

	h = (struct gg_header*) tmp;
	h->type = gg_fix32(type);
	h->length = gg_fix32(tmp_length - sizeof(struct gg_header));

	gg_debug_session(sess, GG_DEBUG_MISC, "STR", gg_fix32(h->type), gg_fix32(h->length));
	gg_debug_dump(sess, GG_DEBUG_DUMP, tmp, tmp_length);

	res = gg_write(sess, tmp, tmp_length);

	free(tmp);

	if (res == -1) {
		gg_debug_session(sess, GG_DEBUG_ERROR, "STR", res, errno, strerror(errno));
		return -1;
	}

	if (sess->async)
		gg_debug_session(sess, GG_DEBUG_NET, "STR", res, tmp_length - res, sess->send_left);

	if (sess->send_buf)
		sess->check |= GG_CHECK_WRITE;

	return 0;
}