static gboolean avdtp_reconf_cmd(struct avdtp *session, uint8_t transaction,
					struct seid_req *req, int size)
{
	struct conf_rej rej;

	rej.error = AVDTP_NOT_SUPPORTED_COMMAND;
	rej.category = 0x00;

	return avdtp_send(session, transaction, AVDTP_MSG_TYPE_REJECT,
					AVDTP_RECONFIGURE, &rej, sizeof(rej));
}