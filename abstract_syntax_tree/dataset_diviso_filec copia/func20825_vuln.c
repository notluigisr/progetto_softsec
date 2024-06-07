static void _gnutls_handshake_internal_state_init(gnutls_session_t session)
{
	
	session->internals.adv_version_major = 0;
	session->internals.adv_version_minor = 0;
	session->internals.direction = 0;

	
	session->internals.last_handshake_in = -1;
	session->internals.last_handshake_out = -1;

	session->internals.resumable = RESUME_TRUE;

	session->internals.handshake_large_loops = 0;
	session->internals.dtls.hsk_read_seq = 0;
	session->internals.dtls.hsk_write_seq = 0;
}