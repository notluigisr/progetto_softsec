static int io_fsetxattr(struct io_kiocb *req, unsigned int issue_flags)
{
	int ret;

	if (issue_flags & IO_URING_F_NONBLOCK)
		return -EAGAIN;

	ret = __io_setxattr(req, issue_flags, &req->file->f_path);
	io_xattr_finish(req, ret);

	return 0;
}