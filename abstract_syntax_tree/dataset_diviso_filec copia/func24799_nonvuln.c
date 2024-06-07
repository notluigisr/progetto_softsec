static int64_t totp_next(gnutls_session_t session)
{
	time_t t;
	uint64_t result;

	t = gnutls_time(NULL);
	if (unlikely(t == (time_t) -1))
		return gnutls_assert_val(GNUTLS_E_INTERNAL_ERROR);

	result = T(session, t);
	if (result == 0)
		return 0;

	if (result == session->key.totp.last_result)
		return 0;

	return result;
}