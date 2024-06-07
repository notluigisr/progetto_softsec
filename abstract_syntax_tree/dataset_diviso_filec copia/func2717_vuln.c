ews_backend_constructed (GObject *object)
{
	EBackend *backend;
	ESource *source;
	ESourceAuthentication *auth_extension;
	const gchar *extension_name;
	gchar *host = NULL;
	guint16 port = 0;

	
	G_OBJECT_CLASS (e_ews_backend_parent_class)->constructed (object);

	backend = E_BACKEND (object);
	source = e_backend_get_source (backend);

	
	e_server_side_source_set_remote_creatable (
		E_SERVER_SIDE_SOURCE (source), TRUE);

	
	extension_name = E_SOURCE_EXTENSION_AUTHENTICATION;
	auth_extension = e_source_get_extension (source, extension_name);

	if (e_backend_get_destination_address (backend, &host, &port)) {
		e_source_authentication_set_host (auth_extension, host);
		e_source_authentication_set_port (auth_extension, port);
	}

	g_free (host);

	
	e_backend_set_connectable (backend, NULL);
}