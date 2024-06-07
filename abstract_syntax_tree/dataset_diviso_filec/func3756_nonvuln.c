R_API RBuffer *r_buf_new_mmap(const char *filename, int perm) {
	r_return_val_if_fail (filename, NULL);
	struct buf_mmap_user u = { 0 };
	u.filename = filename;
	u.perm = perm;
	return new_buffer (R_BUFFER_MMAP, &u);
}