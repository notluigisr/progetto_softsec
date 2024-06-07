static gboolean seid_rej_to_err(struct seid_rej *rej, unsigned int size,
					struct avdtp_error *err)
{
	if (size < sizeof(struct seid_rej)) {
		error("STR");
		return FALSE;
	}

	avdtp_error_init(err, 0x00, rej->error);

	return TRUE;
}