static int check_pe64_buf(RBuffer *buf, ut64 length) {
	int idx, ret = false;
	if (!buf || length <= 0x3d) {
		return false;
	}
	idx = r_buf_read8_at (buf, 0x3c) | (r_buf_read8_at (buf, 0x3d)<<8);
	if (length >= idx + 0x20) {
		ut8 tmp1[2], tmp2[2], tmp3[2];
		r_buf_read_at (buf, 0, tmp1, 2);
		r_buf_read_at (buf, idx, tmp2, 2);
		r_buf_read_at (buf, idx + 0x18, tmp3, 2);
		if (!memcmp (tmp1, "STR", 2)) {
			ret = true;
		}
	}
	return ret;
}