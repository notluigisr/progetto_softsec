evbuffer_add_reference(struct evbuffer *outbuf,
    const void *data, size_t datlen,
    evbuffer_ref_cleanup_cb cleanupfn, void *extra)
{
	struct evbuffer_chain *chain;
	struct evbuffer_chain_reference *info;
	int result = -1;

	chain = evbuffer_chain_new(sizeof(struct evbuffer_chain_reference));
	if (!chain)
		return (-1);
	chain->flags |= EVBUFFER_REFERENCE | EVBUFFER_IMMUTABLE;
	chain->buffer = (u_char *)data;
	chain->buffer_len = datlen;
	chain->off = datlen;

	info = EVBUFFER_CHAIN_EXTRA(struct evbuffer_chain_reference, chain);
	info->cleanupfn = cleanupfn;
	info->extra = extra;

	EVBUFFER_LOCK(outbuf);
	if (outbuf->freeze_end) {
		
		mm_free(chain);
		goto done;
	}
	evbuffer_chain_insert(outbuf, chain);
	outbuf->n_add_for_cb += datlen;

	evbuffer_invoke_callbacks(outbuf);

	result = 0;
done:
	EVBUFFER_UNLOCK(outbuf);

	return result;
}