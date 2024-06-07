ews_connection_utils_setup_bearer_auth (EEwsConnection *cnc,
					SoupMessage *message,
					gboolean is_in_authenticate_handler,
					ESoupAuthBearer *bearer,
					GCancellable *cancellable,
					GError **error)
{
	ESource *source;
	gchar *access_token = NULL;
	gint expires_in_seconds = -1;
	gboolean success = FALSE;

	g_return_val_if_fail (E_IS_EWS_CONNECTION (cnc), FALSE);
	g_return_val_if_fail (E_IS_SOUP_AUTH_BEARER (bearer), FALSE);

	source = e_ews_connection_get_source (cnc);

	success = e_source_get_oauth2_access_token_sync (source, cancellable,
		&access_token, &expires_in_seconds, error);

	if (success) {
		e_soup_auth_bearer_set_access_token (bearer, access_token, expires_in_seconds);

		if (!is_in_authenticate_handler) {
			SoupSession *session;

			session = e_ews_connection_ref_soup_session (cnc);

			ews_connection_utils_ensure_bearer_auth_usage (session, message, bearer);

			g_clear_object (&session);
		}
	}

	g_free (access_token);

	return success;
}