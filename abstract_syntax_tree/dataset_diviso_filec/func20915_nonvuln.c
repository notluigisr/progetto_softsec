static void reset_adv_link(void)
{
	BT_DBG("");
	prov_clear_tx();

	
	(void)k_work_cancel_delayable(&link.prot_timer);

	if (atomic_test_bit(link.flags, ADV_PROVISIONER)) {
		
		(void)memset(&link, 0, offsetof(struct pb_adv, tx.retransmit));
		link.rx.id = XACT_ID_NVAL;
	} else {
		
		link.id = 0;
		atomic_clear(link.flags);
		link.rx.id = XACT_ID_MAX;
		link.tx.id = XACT_ID_NVAL;
	}

	link.tx.pending_ack = XACT_ID_NVAL;
	link.rx.buf = &rx_buf;
	net_buf_simple_reset(link.rx.buf);
}