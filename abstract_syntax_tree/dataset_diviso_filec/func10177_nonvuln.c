int http_process_tarpit(struct stream *s, struct channel *req, int an_bit)
{
	struct http_txn *txn = s->txn;

	DBG_TRACE_ENTER(STRM_EV_STRM_ANA|STRM_EV_HTTP_ANA, s, txn, &txn->req);
	
	channel_dont_connect(req);
	if ((req->flags & (CF_SHUTR|CF_READ_ERROR)) == 0 &&
	    !tick_is_expired(req->analyse_exp, now_ms)) {
		
		channel_htx_erase(req, htxbuf(&req->buf));
		DBG_TRACE_DEVEL("STR",
				STRM_EV_STRM_ANA|STRM_EV_HTTP_ANA, s, txn);
		return 0;
	}


	
	s->logs.t_queue = tv_ms_elapsed(&s->logs.tv_accept, &now);

	http_reply_and_close(s, txn->status, (!(req->flags & CF_READ_ERROR) ? http_error_message(s) : NULL));

	if (!(s->flags & SF_ERR_MASK))
		s->flags |= SF_ERR_PRXCOND;
	if (!(s->flags & SF_FINST_MASK))
		s->flags |= SF_FINST_T;

	DBG_TRACE_LEAVE(STRM_EV_STRM_ANA|STRM_EV_HTTP_ANA, s, txn);
	return 0;
}