static inline int l2cap_config_rsp(struct l2cap_conn *conn,
				   struct l2cap_cmd_hdr *cmd, u16 cmd_len,
				   u8 *data)
{
	struct l2cap_conf_rsp *rsp = (struct l2cap_conf_rsp *)data;
	u16 scid, flags, result;
	struct l2cap_chan *chan;
	int len = cmd_len - sizeof(*rsp);
	int err = 0;

	if (cmd_len < sizeof(*rsp))
		return -EPROTO;

	scid   = __le16_to_cpu(rsp->scid);
	flags  = __le16_to_cpu(rsp->flags);
	result = __le16_to_cpu(rsp->result);

	BT_DBG("STR", scid, flags,
	       result, len);

	chan = l2cap_get_chan_by_scid(conn, scid);
	if (!chan)
		return 0;

	switch (result) {
	case L2CAP_CONF_SUCCESS:
		l2cap_conf_rfc_get(chan, rsp->data, len);
		clear_bit(CONF_REM_CONF_PEND, &chan->conf_state);
		break;

	case L2CAP_CONF_PENDING:
		set_bit(CONF_REM_CONF_PEND, &chan->conf_state);

		if (test_bit(CONF_LOC_CONF_PEND, &chan->conf_state)) {
			char buf[64];

			len = l2cap_parse_conf_rsp(chan, rsp->data, len,
						   buf, &result);
			if (len < 0) {
				l2cap_send_disconn_req(chan, ECONNRESET);
				goto done;
			}

			if (!chan->hs_hcon) {
				l2cap_send_efs_conf_rsp(chan, buf, cmd->ident,
							0);
			} else {
				if (l2cap_check_efs(chan)) {
					amp_create_logical_link(chan);
					chan->ident = cmd->ident;
				}
			}
		}
		goto done;

	case L2CAP_CONF_UNACCEPT:
		if (chan->num_conf_rsp <= L2CAP_CONF_MAX_CONF_RSP) {
			char req[64];

			if (len > sizeof(req) - sizeof(struct l2cap_conf_req)) {
				l2cap_send_disconn_req(chan, ECONNRESET);
				goto done;
			}

			
			result = L2CAP_CONF_SUCCESS;
			len = l2cap_parse_conf_rsp(chan, rsp->data, len,
						   req, &result);
			if (len < 0) {
				l2cap_send_disconn_req(chan, ECONNRESET);
				goto done;
			}

			l2cap_send_cmd(conn, l2cap_get_ident(conn),
				       L2CAP_CONF_REQ, len, req);
			chan->num_conf_req++;
			if (result != L2CAP_CONF_SUCCESS)
				goto done;
			break;
		}

	default:
		l2cap_chan_set_err(chan, ECONNRESET);

		__set_chan_timer(chan, L2CAP_DISC_REJ_TIMEOUT);
		l2cap_send_disconn_req(chan, ECONNRESET);
		goto done;
	}

	if (flags & L2CAP_CONF_FLAG_CONTINUATION)
		goto done;

	set_bit(CONF_INPUT_DONE, &chan->conf_state);

	if (test_bit(CONF_OUTPUT_DONE, &chan->conf_state)) {
		set_default_fcs(chan);

		if (chan->mode == L2CAP_MODE_ERTM ||
		    chan->mode == L2CAP_MODE_STREAMING)
			err = l2cap_ertm_init(chan);

		if (err < 0)
			l2cap_send_disconn_req(chan, -err);
		else
			l2cap_chan_ready(chan);
	}

done:
	l2cap_chan_unlock(chan);
	return err;
}