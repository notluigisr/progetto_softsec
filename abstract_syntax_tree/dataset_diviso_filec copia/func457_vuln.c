static void sctp_assoc_bh_rcv(struct work_struct *work)
{
	struct sctp_association *asoc =
		container_of(work, struct sctp_association,
			     base.inqueue.immediate);
	struct sctp_endpoint *ep;
	struct sctp_chunk *chunk;
	struct sock *sk;
	struct sctp_inq *inqueue;
	int state;
	sctp_subtype_t subtype;
	int error = 0;

	
	ep = asoc->ep;
	sk = asoc->base.sk;

	inqueue = &asoc->base.inqueue;
	sctp_association_hold(asoc);
	while (NULL != (chunk = sctp_inq_pop(inqueue))) {
		state = asoc->state;
		subtype = SCTP_ST_CHUNK(chunk->chunk_hdr->type);

		
		if (sctp_chunk_is_data(chunk))
			asoc->peer.last_data_from = chunk->transport;
		else
			SCTP_INC_STATS(SCTP_MIB_INCTRLCHUNKS);

		if (chunk->transport)
			chunk->transport->last_time_heard = jiffies;

		
		error = sctp_do_sm(SCTP_EVENT_T_CHUNK, subtype,
				   state, ep, asoc, chunk, GFP_ATOMIC);

		
		if (asoc->base.dead)
			break;

		
		if (error && chunk)
			chunk->pdiscard = 1;
	}
	sctp_association_put(asoc);
}