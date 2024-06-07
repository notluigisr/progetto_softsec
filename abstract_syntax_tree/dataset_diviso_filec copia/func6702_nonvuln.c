ssize_t lxc_sendfile_nointr(int out_fd, int in_fd, off_t *offset, size_t count)
{
	ssize_t ret;

again:
	ret = sendfile(out_fd, in_fd, offset, count);
	if (ret < 0) {
		if (errno == EINTR)
			goto again;

		return -1;
	}

	return ret;
}