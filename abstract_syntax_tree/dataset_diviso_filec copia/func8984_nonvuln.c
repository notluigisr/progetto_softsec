static struct io_wq_work *io_steal_work(struct io_kiocb *req)
{
	struct io_kiocb *nxt;

	
	if (refcount_read(&req->refs) != 1)
		return NULL;

	nxt = io_req_find_next(req);
	return nxt ? &nxt->work : NULL;
}