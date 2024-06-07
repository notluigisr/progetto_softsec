static int send_req(struct avdtp *session, gboolean priority,
			struct pending_req *req)
{
	static int transaction = 0;
	int err, timeout;

	if (session->state == AVDTP_SESSION_STATE_DISCONNECTED) {
		BtIOMode mode = btd_opts.avdtp.session_mode;

		session->io = l2cap_connect(session, mode);
		if (!session->io) {
			
			avdtp_set_state(session,
					AVDTP_SESSION_STATE_DISCONNECTED);
			err = -EIO;
			goto failed;
		}
		avdtp_set_state(session, AVDTP_SESSION_STATE_CONNECTING);
	}

	if (session->state < AVDTP_SESSION_STATE_CONNECTED ||
			session->req != NULL) {
		queue_request(session, req, priority);
		return 0;
	}

	req->transaction = transaction++;
	transaction %= 16;

	
	if (!avdtp_send(session, req->transaction, AVDTP_MSG_TYPE_COMMAND,
				req->signal_id, req->data, req->data_size)) {
		err = -EIO;
		goto failed;
	}

	session->req = req;

	switch (req->signal_id) {
	case AVDTP_ABORT:
		timeout = ABORT_TIMEOUT;
		break;
	case AVDTP_SUSPEND:
		timeout = SUSPEND_TIMEOUT;
		break;
	default:
		timeout = REQ_TIMEOUT;
	}

	req->timeout = timeout_add_seconds(timeout, request_timeout,
						session, NULL);
	return 0;

failed:
	g_free(req->data);
	g_free(req);
	return err;
}