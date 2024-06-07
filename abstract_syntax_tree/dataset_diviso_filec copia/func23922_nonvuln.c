static struct io_kiocb *io_get_req(struct io_ring_ctx *ctx,
				   struct io_submit_state *state)
{
	gfp_t gfp = GFP_KERNEL | __GFP_NOWARN;
	struct io_kiocb *req;

	if (!percpu_ref_tryget(&ctx->refs))
		return NULL;

	if (!state) {
		req = kmem_cache_alloc(req_cachep, gfp);
		if (unlikely(!req))
			goto fallback;
	} else if (!state->free_reqs) {
		size_t sz;
		int ret;

		sz = min_t(size_t, state->ios_left, ARRAY_SIZE(state->reqs));
		ret = kmem_cache_alloc_bulk(req_cachep, gfp, sz, state->reqs);

		
		if (unlikely(ret <= 0)) {
			state->reqs[0] = kmem_cache_alloc(req_cachep, gfp);
			if (!state->reqs[0])
				goto fallback;
			ret = 1;
		}
		state->free_reqs = ret - 1;
		state->cur_req = 1;
		req = state->reqs[0];
	} else {
		req = state->reqs[state->cur_req];
		state->free_reqs--;
		state->cur_req++;
	}

got_it:
	req->file = NULL;
	req->ctx = ctx;
	req->flags = 0;
	
	refcount_set(&req->refs, 2);
	req->result = 0;
	INIT_IO_WORK(&req->work, io_wq_submit_work);
	return req;
fallback:
	req = io_get_fallback_req(ctx);
	if (req)
		goto got_it;
	percpu_ref_put(&ctx->refs);
	return NULL;
}