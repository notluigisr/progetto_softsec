jpc_mqdec_t *jpc_mqdec_create(int maxctxs, jas_stream_t *in)
{
	jpc_mqdec_t *mqdec;

	
	assert(maxctxs > 0);

	
	if (!(mqdec = jas_malloc(sizeof(jpc_mqdec_t)))) {
		goto error;
	}
	mqdec->in = in;
	mqdec->maxctxs = maxctxs;
	
	if (!(mqdec->ctxs = jas_malloc(mqdec->maxctxs * sizeof(jpc_mqstate_t *)))) {
		goto error;
	}
	
	mqdec->curctx = mqdec->ctxs;

	
	if (mqdec->in) {
		jpc_mqdec_init(mqdec);
	}
	
	jpc_mqdec_setctxs(mqdec, 0, 0);

	return mqdec;

error:
	
	if (mqdec) {
		jpc_mqdec_destroy(mqdec);
	}
	return 0;
}