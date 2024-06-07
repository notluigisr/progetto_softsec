static int io_fallocate(struct io_kiocb *req, unsigned int issue_flags)
{
	int ret;

	
	if (issue_flags & IO_URING_F_NONBLOCK)
		return -EAGAIN;
	ret = vfs_fallocate(req->file, req->sync.mode, req->sync.off,
				req->sync.len);
	if (ret >= 0)
		fsnotify_modify(req->file);
	io_req_complete(req, ret);
	return 0;
}