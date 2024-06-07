size_t copy_to_iter(const void *addr, size_t bytes, struct iov_iter *i)
{
	const char *from = addr;
	if (unlikely(i->type & ITER_PIPE))
		return copy_pipe_to_iter(addr, bytes, i);
	iterate_and_advance(i, bytes, v,
		__copy_to_user(v.iov_base, (from += v.iov_len) - v.iov_len,
			       v.iov_len),
		memcpy_to_page(v.bv_page, v.bv_offset,
			       (from += v.bv_len) - v.bv_len, v.bv_len),
		memcpy(v.iov_base, (from += v.iov_len) - v.iov_len, v.iov_len)
	)

	return bytes;
}