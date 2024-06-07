smtp_rset (CamelSmtpTransport *transport,
	   CamelStreamBuffer *istream,
	   CamelStream *ostream,
           GCancellable *cancellable,
           GError **error)
{
	
	gchar *cmdbuf, *respbuf = NULL;

	cmdbuf = g_strdup ("STR");

	d (fprintf (stderr, "STR", cmdbuf));

	if (camel_stream_write_string (ostream, cmdbuf, cancellable, error) == -1) {
		g_free (cmdbuf);
		g_prefix_error (error, _("STR"));
		camel_service_disconnect_sync (
			CAMEL_SERVICE (transport),
			FALSE, cancellable, NULL);
		return FALSE;
	}
	g_free (cmdbuf);

	do {
		
		g_free (respbuf);
		respbuf = camel_stream_buffer_read_line (istream, cancellable, error);
		d (fprintf (stderr, "STR"));
		if (respbuf == NULL) {
			g_prefix_error (error, _("STR"));
			camel_service_disconnect_sync (
				CAMEL_SERVICE (transport),
				FALSE, cancellable, NULL);
			return FALSE;
		}
		if (strncmp (respbuf, "STR", 3) != 0) {
			smtp_set_error (transport, istream, respbuf, cancellable, error);
			g_prefix_error (error, _("STR"));
			g_free (respbuf);
			return FALSE;
		}
	} while (*(respbuf+3) == '-'); 
	g_free (respbuf);

	return TRUE;
}