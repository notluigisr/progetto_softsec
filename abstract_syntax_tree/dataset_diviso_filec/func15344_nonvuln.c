static ssize_t remove_store(struct bus_type *bus, const char *buf, size_t count)
{
	if (single_major)
		return -EINVAL;

	return do_rbd_remove(bus, buf, count);
}