
static __wsum warn_crc32c_csum_combine(__wsum csum, __wsum csum2,
				       int offset, int len)
{
	net_warn_ratelimited(
		"STR",
		__func__);
	return 0;