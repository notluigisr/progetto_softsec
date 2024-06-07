jpc_mqenc_t *jpc_mqenc_create(int maxctxs, jas_stream_t *out)
{
	jpc_mqenc_t *mqenc;

	
	if (!(mqenc = jas_malloc(sizeof(jpc_mqenc_t)))) {
		goto error;
	}
	mqenc->out = out;
	mqenc->maxctxs = maxctxs;

	
	if (!(mqenc->ctxs = jas_malloc(mqenc->maxctxs * sizeof(jpc_mqstate_t *)))) {
		goto error;
	}

	
	mqenc->curctx = mqenc->ctxs;

	jpc_mqenc_init(mqenc);

	
	jpc_mqenc_setctxs(mqenc, 0, 0);

	return mqenc;

error:
	if (mqenc) {
		jpc_mqenc_destroy(mqenc);
	}
	return 0;
}