void tipc_link_bc_init_rcv(struct tipc_link *l, struct tipc_msg *hdr)
{
	int mtyp = msg_type(hdr);
	u16 peers_snd_nxt = msg_bc_snd_nxt(hdr);

	if (link_is_up(l))
		return;

	if (msg_user(hdr) == BCAST_PROTOCOL) {
		l->rcv_nxt = peers_snd_nxt;
		l->state = LINK_ESTABLISHED;
		return;
	}

	if (l->peer_caps & TIPC_BCAST_SYNCH)
		return;

	if (msg_peer_node_is_up(hdr))
		return;

	
	if ((mtyp == RESET_MSG) || (mtyp == ACTIVATE_MSG))
		l->rcv_nxt = peers_snd_nxt;
}