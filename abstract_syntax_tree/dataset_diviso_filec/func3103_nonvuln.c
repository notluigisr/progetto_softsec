static void __io_req_complete_put(struct io_kiocb *req)
{
	
	if (req_ref_put_and_test(req)) {
		struct io_ring_ctx *ctx = req->ctx;

		if (req->flags & IO_REQ_LINK_FLAGS) {
			if (req->flags & IO_DISARM_MASK)
				io_disarm_next(req);
			if (req->link) {
				io_req_task_queue(req->link);
				req->link = NULL;
			}
		}
		io_req_put_rsrc(req);
		
		io_put_kbuf_comp(req);
		io_dismantle_req(req);
		io_put_task(req->task, 1);
		wq_list_add_head(&req->comp_list, &ctx->locked_free_list);
		ctx->locked_free_nr++;
	}
}