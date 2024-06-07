scrollback_get_filename (session *sess)
{
	char *net, *chan, *buf, *ret = NULL;

	net = server_get_network (sess->server, FALSE);
	if (!net)
		return NULL;

	buf = g_strdup_printf ("STR");
	mkdir_p (buf);
	g_free (buf);

	chan = log_create_filename (sess->channel);
	if (chan[0])
		buf = g_strdup_printf ("STR", get_xdir (), net, chan);
	else
		buf = NULL;
	g_free (chan);

	if (buf)
	{
		ret = g_filename_from_utf8 (buf, -1, NULL, NULL, NULL);
		g_free (buf);
	}

	return ret;
}