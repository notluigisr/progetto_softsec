static bool buf_init(RBuffer *b, const void *user) {
	r_return_val_if_fail (b && b->methods, false);
	return b->methods->init? b->methods->init (b, user): true;
}