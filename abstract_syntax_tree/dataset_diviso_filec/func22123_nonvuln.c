R_API st64 r_buf_insert_bytes(RBuffer *b, ut64 addr, const ut8 *buf, ut64 length) {
	r_return_val_if_fail (b && !b->readonly, -1);
	st64 pos, r = r_buf_seek (b, 0, R_BUF_CUR);
	if (r < 0) {
		return r;
	}
	pos = r;
	r = r_buf_seek (b, addr, R_BUF_SET);
	if (r < 0) {
		goto restore_pos;
	}

	ut64 sz = r_buf_size (b);
	ut8 *tmp = R_NEWS (ut8, sz - addr);
	r = r_buf_read (b, tmp, sz - addr);
	if (r < 0) {
		goto free_tmp;
	}
	st64 tmp_length = r;
	if (!r_buf_resize (b, sz + length)) {
		goto free_tmp;
	}
	r = r_buf_seek (b, addr + length, R_BUF_SET);
	if (r < 0) {
		goto free_tmp;
	}
	r = r_buf_write (b, tmp, tmp_length);
	if (r < 0) {
		goto free_tmp;
	}
	r = r_buf_seek (b, addr, R_BUF_SET);
	if (r < 0) {
		goto free_tmp;
	}
	r = r_buf_write (b, buf, length);
free_tmp:
	free (tmp);
restore_pos:
	r_buf_seek (b, pos, R_BUF_SET);
	return r;
}