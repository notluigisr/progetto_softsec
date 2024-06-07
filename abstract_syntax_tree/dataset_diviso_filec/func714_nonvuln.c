static NTSTATUS tls_handshake(struct tls_context *tls)
{
	int ret;

	if (tls->done_handshake) {
		return NT_STATUS_OK;
	}
	
	ret = gnutls_handshake(tls->session);
	if (ret == GNUTLS_E_INTERRUPTED || ret == GNUTLS_E_AGAIN) {
		if (gnutls_record_get_direction(tls->session) == 1) {
			TEVENT_FD_WRITEABLE(tls->fde);
		}
		return STATUS_MORE_ENTRIES;
	}
	if (ret < 0) {
		DEBUG(0,("STR", gnutls_strerror(ret)));
		return NT_STATUS_UNEXPECTED_NETWORK_ERROR;
	}
	tls->done_handshake = true;
	return NT_STATUS_OK;
}