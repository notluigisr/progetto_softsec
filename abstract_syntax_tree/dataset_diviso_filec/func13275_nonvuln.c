sctp_disposition_t sctp_sf_cookie_wait_prm_abort(
	const struct sctp_endpoint *ep,
	const struct sctp_association *asoc,
	const sctp_subtype_t type,
	void *arg,
	sctp_cmd_seq_t *commands)
{
	struct msghdr *msg = arg;
	struct sctp_chunk *abort;
	sctp_disposition_t retval;

	
	sctp_add_cmd_sf(commands, SCTP_CMD_TIMER_STOP,
			SCTP_TO(SCTP_EVENT_TIMEOUT_T1_INIT));
	retval = SCTP_DISPOSITION_CONSUME;

	
	abort = sctp_make_abort_user(asoc, NULL, msg);
	if (!abort)
		retval = SCTP_DISPOSITION_NOMEM;
	else
		sctp_add_cmd_sf(commands, SCTP_CMD_REPLY, SCTP_CHUNK(abort));

	sctp_add_cmd_sf(commands, SCTP_CMD_NEW_STATE,
			SCTP_STATE(SCTP_STATE_CLOSED));

	SCTP_INC_STATS(SCTP_MIB_ABORTEDS);

	

	
	sctp_add_cmd_sf(commands, SCTP_CMD_INIT_FAILED,
			SCTP_U32(SCTP_ERROR_USER_ABORT));

	return retval;
}