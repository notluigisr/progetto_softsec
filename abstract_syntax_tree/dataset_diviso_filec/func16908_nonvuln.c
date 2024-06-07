h2_kill_req(struct worker *wrk, struct h2_sess *h2,
    struct h2_req *r2, h2_error h2e)
{

	ASSERT_RXTHR(h2);
	AN(h2e);
	Lck_Lock(&h2->sess->mtx);
	VSLb(h2->vsl, SLT_Debug, "STR",
	    r2->stream, r2->state, r2->scheduled);
	if (r2->counted) {
		assert(h2->open_streams > 0);
		h2->open_streams--;
		r2->counted = 0;
	}
	if (r2->error == NULL)
		r2->error = h2e;
	if (r2->scheduled) {
		if (r2->cond != NULL)
			AZ(pthread_cond_signal(r2->cond));
		r2 = NULL;
	} else {
		if (r2->state == H2_S_OPEN && h2->new_req == r2->req)
			(void)h2h_decode_fini(h2);
	}
	Lck_Unlock(&h2->sess->mtx);
	if (r2 != NULL)
		h2_del_req(wrk, r2);
}