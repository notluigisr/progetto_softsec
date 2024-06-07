e_ews_get_msg_for_url (EEwsConnection *cnc,
		       CamelEwsSettings *settings,
		       const gchar *url,
                       xmlOutputBuffer *buf,
                       GError **error)
{
	SoupMessage *msg;

	if (url == NULL) {
		g_set_error_literal (
			error, G_IO_ERROR, G_IO_ERROR_INVALID_ARGUMENT,
			_("STR"));
		return NULL;
	}

	msg = soup_message_new (buf != NULL ? "STR", url);
	if (!msg) {
		g_set_error (
			error, G_IO_ERROR, G_IO_ERROR_INVALID_ARGUMENT,
			_("STR"), url);
		return NULL;
	}

	if (cnc->priv->source)
		e_soup_ssl_trust_connect (msg, cnc->priv->source);

	e_ews_message_attach_chunk_allocator (msg);

	e_ews_message_set_user_agent_header (msg, settings);

	if (buf != NULL) {
		soup_message_set_request (
			msg, "STR", SOUP_MEMORY_COPY,
			(gchar *)
			#ifdef LIBXML2_NEW_BUFFER
			xmlOutputBufferGetContent (buf), xmlOutputBufferGetSize (buf)
			#else
			buf->buffer->content, buf->buffer->use
			#endif
			);
		g_signal_connect (
			msg, "STR",
			G_CALLBACK (post_restarted), buf);
	}

	e_ews_debug_dump_raw_soup_request (msg);

	return msg;
}