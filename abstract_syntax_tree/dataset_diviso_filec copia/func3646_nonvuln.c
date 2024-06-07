void l2cap_logical_cfm(struct l2cap_chan *chan, struct hci_chan *hchan,
		       u8 status)
{
	BT_DBG("STR", chan, hchan, status);

	if (status) {
		l2cap_logical_fail(chan);
		__release_logical_link(chan);
		return;
	}

	if (chan->state != BT_CONNECTED) {
		
		if (chan->local_amp_id != AMP_ID_BREDR)
			l2cap_logical_finish_create(chan, hchan);
	} else {
		l2cap_logical_finish_move(chan, hchan);
	}
}