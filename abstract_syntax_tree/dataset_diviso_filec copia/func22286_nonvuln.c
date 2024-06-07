struct sctp_chunk *sctp_chunkify(struct sk_buff *skb,
			    const struct sctp_association *asoc,
			    struct sock *sk)
{
	struct sctp_chunk *retval;

	retval = kmem_cache_zalloc(sctp_chunk_cachep, GFP_ATOMIC);

	if (!retval)
		goto nodata;

	if (!sk) {
		SCTP_DEBUG_PRINTK("STR", skb);
	}

	INIT_LIST_HEAD(&retval->list);
	retval->skb		= skb;
	retval->asoc		= (struct sctp_association *)asoc;
	retval->has_tsn		= 0;
	retval->has_ssn         = 0;
	retval->rtt_in_progress	= 0;
	retval->sent_at		= 0;
	retval->singleton	= 1;
	retval->end_of_packet	= 0;
	retval->ecn_ce_done	= 0;
	retval->pdiscard	= 0;

	
	retval->tsn_missing_report = 0;
	retval->tsn_gap_acked = 0;
	retval->fast_retransmit = SCTP_CAN_FRTX;

	
	retval->msg = NULL;

	
	INIT_LIST_HEAD(&retval->transmitted_list);
	INIT_LIST_HEAD(&retval->frag_list);
	SCTP_DBG_OBJCNT_INC(chunk);
	atomic_set(&retval->refcnt, 1);

nodata:
	return retval;
}