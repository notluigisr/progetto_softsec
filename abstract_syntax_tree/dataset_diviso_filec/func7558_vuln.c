 */
static void io_drop_inflight_file(struct io_kiocb *req)
{
	if (unlikely(req->flags & REQ_F_INFLIGHT)) {
		fput(req->file);
		req->file = NULL;
		req->flags &= ~REQ_F_INFLIGHT;
	}