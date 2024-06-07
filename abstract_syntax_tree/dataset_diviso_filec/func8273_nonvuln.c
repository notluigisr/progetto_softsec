seamless_send_zchange(unsigned long id, unsigned long below, unsigned long flags)
{
	if (!g_seamless_rdp)
		return (unsigned int) -1;

	return seamless_send("STR", id, below, flags);
}