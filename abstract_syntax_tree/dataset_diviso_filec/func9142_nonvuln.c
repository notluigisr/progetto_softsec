qb_rb_open(const char *name, size_t size, uint32_t flags,
	   size_t shared_user_data_size)
{
	return qb_rb_open_2(name, size, flags, shared_user_data_size, NULL);
}