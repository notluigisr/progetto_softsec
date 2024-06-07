seamless_send_state(unsigned long id, unsigned int state, unsigned long flags)
{
	if (!g_seamless_rdp)
		return (unsigned int) -1;

	return seamless_send("STR", id, state, flags);
}