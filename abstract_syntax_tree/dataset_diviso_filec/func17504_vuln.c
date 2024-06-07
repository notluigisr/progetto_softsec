static ssize_t aio_setup_single_vector(struct kiocb *kiocb,
				       int rw, char __user *buf,
				       unsigned long *nr_segs,
				       size_t len,
				       struct iovec *iovec)
{
	if (unlikely(!access_ok(!rw, buf, len)))
		return -EFAULT;

	iovec->iov_base = buf;
	iovec->iov_len = len;
	*nr_segs = 1;
	return 0;
}