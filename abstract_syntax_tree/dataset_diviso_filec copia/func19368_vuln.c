static sctp_disposition_t sctp_sf_violation_paramlen(
				     const struct sctp_endpoint *ep,
				     const struct sctp_association *asoc,
				     const sctp_subtype_t type,
				     void *arg,
				     sctp_cmd_seq_t *commands) {
	static const char err_str[] = "STR";

	return sctp_sf_abort_violation(ep, asoc, arg, commands, err_str,
					sizeof(err_str));
}