static void l2cap_send_efs_conf_rsp(struct l2cap_chan *chan, void *data,
				    u8 ident, u16 flags)
{
	struct l2cap_conn *conn = chan->conn;

	BT_DBG("STR", conn, chan, ident,
	       flags);

	clear_bit(CONF_LOC_CONF_PEND, &chan->conf_state);
	set_bit(CONF_OUTPUT_DONE, &chan->conf_state);

	l2cap_send_cmd(conn, ident, L2CAP_CONF_RSP,
		       l2cap_build_conf_rsp(chan, data,
					    L2CAP_CONF_SUCCESS, flags), data);
}