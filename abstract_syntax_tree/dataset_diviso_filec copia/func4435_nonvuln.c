static gboolean avdtp_discover_cmd(struct avdtp *session, uint8_t transaction,
							void *buf, int size)
{
	unsigned int rsp_size, sep_count;
	struct seid_info *seps, *p;
	gboolean ret;

	sep_count = queue_length(session->lseps);

	if (sep_count == 0) {
		uint8_t err = AVDTP_NOT_SUPPORTED_COMMAND;
		return avdtp_send(session, transaction, AVDTP_MSG_TYPE_REJECT,
					AVDTP_DISCOVER, &err, sizeof(err));
	}

	rsp_size = sep_count * sizeof(struct seid_info);

	seps = g_new0(struct seid_info, sep_count);
	p = seps;

	queue_foreach(session->lseps, copy_seps, &p);

	ret = avdtp_send(session, transaction, AVDTP_MSG_TYPE_ACCEPT,
				AVDTP_DISCOVER, seps, rsp_size);
	g_free(seps);

	return ret;
}