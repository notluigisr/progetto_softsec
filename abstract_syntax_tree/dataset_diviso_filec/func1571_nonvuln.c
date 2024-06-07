R_API bool r_buf_append_ut32(RBuffer *b, ut32 n) {
	r_return_val_if_fail (b && !b->readonly, false);
	return r_buf_append_bytes (b, (const ut8 *)&n, sizeof (n));
}