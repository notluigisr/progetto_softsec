static int io_send(struct io_kiocb *req, struct io_kiocb **nxt,
		   bool force_nonblock)
{
#if defined(CONFIG_NET)
	struct socket *sock;
	int ret;

	if (unlikely(req->ctx->flags & IORING_SETUP_IOPOLL))
		return -EINVAL;

	sock = sock_from_file(req->file, &ret);
	if (sock) {
		struct io_sr_msg *sr = &req->sr_msg;
		struct msghdr msg;
		struct iovec iov;
		unsigned flags;

		ret = import_single_range(WRITE, sr->buf, sr->len, &iov,
						&msg.msg_iter);
		if (ret)
			return ret;

		msg.msg_name = NULL;
		msg.msg_control = NULL;
		msg.msg_controllen = 0;
		msg.msg_namelen = 0;

		flags = req->sr_msg.msg_flags;
		if (flags & MSG_DONTWAIT)
			req->flags |= REQ_F_NOWAIT;
		else if (force_nonblock)
			flags |= MSG_DONTWAIT;

		msg.msg_flags = flags;
		ret = sock_sendmsg(sock, &msg);
		if (force_nonblock && ret == -EAGAIN)
			return -EAGAIN;
		if (ret == -ERESTARTSYS)
			ret = -EINTR;
	}

	io_cqring_add_event(req, ret);
	if (ret < 0)
		req_set_fail_links(req);
	io_put_req_find_next(req, nxt);
	return 0;
#else
	return -EOPNOTSUPP;
#endif
}