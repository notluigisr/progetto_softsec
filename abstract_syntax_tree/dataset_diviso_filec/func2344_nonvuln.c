void _gnutls_set_session_ticket_key_rotation_callback(gnutls_session_t session, gnutls_stek_rotation_callback_t cb)
{
	if (session)
		session->key.totp.cb = cb;
}