dtls1_buffer_message(SSL *s, int is_ccs)
	{
	pitem *item;
	hm_fragment *frag;
	PQ_64BIT seq64;

	
	OPENSSL_assert(s->init_off == 0);

	frag = dtls1_hm_fragment_new(s->init_num);

	memcpy(frag->fragment, s->init_buf->data, s->init_num);

	if ( is_ccs)
		{
		OPENSSL_assert(s->d1->w_msg_hdr.msg_len + 
			DTLS1_CCS_HEADER_LENGTH <= (unsigned int)s->init_num);
		}
	else
		{
		OPENSSL_assert(s->d1->w_msg_hdr.msg_len + 
			DTLS1_HM_HEADER_LENGTH == (unsigned int)s->init_num);
		}

	frag->msg_header.msg_len = s->d1->w_msg_hdr.msg_len;
	frag->msg_header.seq = s->d1->w_msg_hdr.seq;
	frag->msg_header.type = s->d1->w_msg_hdr.type;
	frag->msg_header.frag_off = 0;
	frag->msg_header.frag_len = s->d1->w_msg_hdr.msg_len;
	frag->msg_header.is_ccs = is_ccs;

	
	frag->msg_header.saved_retransmit_state.enc_write_ctx = s->enc_write_ctx;
	frag->msg_header.saved_retransmit_state.write_hash = s->write_hash;
	frag->msg_header.saved_retransmit_state.compress = s->compress;
	frag->msg_header.saved_retransmit_state.session = s->session;
	frag->msg_header.saved_retransmit_state.epoch = s->d1->w_epoch;

	pq_64bit_init(&seq64);

	pq_64bit_assign_word(&seq64,
						 dtls1_get_queue_priority(frag->msg_header.seq,
												  frag->msg_header.is_ccs));
		
	item = pitem_new(seq64, frag);
	pq_64bit_free(&seq64);
	if ( item == NULL)
		{
		dtls1_hm_fragment_free(frag);
		return 0;
		}

#if 0
	fprintf( stderr, "STR", msg_buf->type);
	fprintf( stderr, "STR", msg_buf->len);
	fprintf( stderr, "STR", msg_buf->seq_num);
#endif

	pqueue_insert(s->d1->sent_messages, item);
	return 1;
	}