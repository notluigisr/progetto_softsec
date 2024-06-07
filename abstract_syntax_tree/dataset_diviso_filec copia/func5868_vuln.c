static ssize_t rebind_store(struct device_driver *dev, const char *buf,
				 size_t count)
{
	int ret;
	int len;
	struct bus_id_priv *bid;

	
	len = strnlen(buf, BUSID_SIZE);

	if (!(len < BUSID_SIZE))
		return -EINVAL;

	bid = get_busid_priv(buf);
	if (!bid)
		return -ENODEV;

	
	bid->status = STUB_BUSID_OTHER;

	ret = do_rebind((char *) buf, bid);
	if (ret < 0)
		return ret;

	
	del_match_busid((char *) buf);

	return count;
}