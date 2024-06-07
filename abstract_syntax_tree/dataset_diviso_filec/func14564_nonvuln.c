size_t winsdb_addr_list_length(struct winsdb_addr **addresses)
{
	size_t i;
	for (i=0; addresses[i]; i++);
	return i;
}