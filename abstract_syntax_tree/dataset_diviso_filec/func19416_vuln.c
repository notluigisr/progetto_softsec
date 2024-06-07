h2_end_headers(struct worker *wrk, struct h2_sess *h2,
    struct req *req, struct h2_req *r2)
{
	h2_error h2e;
	const char *b;

	ASSERT_RXTHR(h2);
	assert(r2->state == H2_S_OPEN);
	h2e = h2h_decode_fini(h2);
	h2->new_req = NULL;
	if (r2->req->req_body_status == REQ_BODY_NONE) {
		
		r2->state = H2_S_CLOS_REM;
	}
	if (h2e != NULL) {
		Lck_Lock(&h2->sess->mtx);
		VSLb(h2->vsl, SLT_Debug, "STR", h2e->name);
		Lck_Unlock(&h2->sess->mtx);
		AZ(r2->req->ws->r);
		h2_del_req(wrk, r2);
		return (h2e);
	}
	VSLb_ts_req(req, "STR", req->t_req);

	
	
	
	http_CollectHdrSep(req->http, H_Cookie, "STR");	

	if (req->req_body_status == REQ_BODY_INIT) {
		if (!http_GetHdr(req->http, H_Content_Length, &b))
			req->req_body_status = REQ_BODY_WITHOUT_LEN;
		else
			req->req_body_status = REQ_BODY_WITH_LEN;
	} else {
		assert (req->req_body_status == REQ_BODY_NONE);
		if (http_GetContentLength(req->http) > 0)
			return (H2CE_PROTOCOL_ERROR); 
	}

	if (req->http->hd[HTTP_HDR_METHOD].b == NULL) {
		VSLb(h2->vsl, SLT_Debug, "STR");
		return (H2SE_PROTOCOL_ERROR); 
	}
	if (req->http->hd[HTTP_HDR_URL].b == NULL) {
		VSLb(h2->vsl, SLT_Debug, "STR");
		return (H2SE_PROTOCOL_ERROR); 
	}
	AN(req->http->hd[HTTP_HDR_PROTO].b);

	req->req_step = R_STP_TRANSPORT;
	req->task.func = h2_do_req;
	req->task.priv = req;
	r2->scheduled = 1;
	if (Pool_Task(wrk->pool, &req->task, TASK_QUEUE_STR) != 0) {
		r2->scheduled = 0;
		r2->state = H2_S_CLOSED;
		return (H2SE_REFUSED_STREAM); 
	}
	return (0);
}