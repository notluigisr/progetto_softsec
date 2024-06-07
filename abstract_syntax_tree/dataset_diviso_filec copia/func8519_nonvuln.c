static int io_fallocate(struct io_kiocb *req, struct io_kiocb **nxt,
			bool force_nonblock)
{
	struct io_wq_work *work, *old_work;

	
	if (force_nonblock) {
		io_put_req(req);
		req->work.func = io_fallocate_finish;
		return -EAGAIN;
	}

	work = old_work = &req->work;
	io_fallocate_finish(&work);
	if (work && work != old_work)
		*nxt = container_of(work, struct io_kiocb, work);

	return 0;
}