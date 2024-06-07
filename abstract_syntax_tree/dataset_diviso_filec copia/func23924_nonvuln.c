static inline bool __io_fill_cqe_req(struct io_kiocb *req, s32 res, u32 cflags)
{
	trace_io_uring_complete(req->ctx, req, req->cqe.user_data, res, cflags, 0, 0);
	return __io_fill_cqe(req->ctx, req->cqe.user_data, res, cflags);
}