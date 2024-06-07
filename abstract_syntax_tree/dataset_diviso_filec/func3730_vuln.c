void sctp_transport_reset(struct sctp_transport *t)
{
	struct sctp_association *asoc = t->asoc;

	
	t->cwnd = min(4*asoc->pathmtu, max_t(__u32, 2*asoc->pathmtu, 4380));
	t->burst_limited = 0;
	t->ssthresh = asoc->peer.i.a_rwnd;
	t->rto = asoc->rto_initial;
	t->rtt = 0;
	t->srtt = 0;
	t->rttvar = 0;

	
	t->partial_bytes_acked = 0;
	t->flight_size = 0;
	t->error_count = 0;
	t->rto_pending = 0;
	t->hb_sent = 0;

	
	t->cacc.changeover_active = 0;
	t->cacc.cycling_changeover = 0;
	t->cacc.next_tsn_at_change = 0;
	t->cacc.cacc_saw_newack = 0;
}