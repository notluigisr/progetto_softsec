static int _free_pwd_session (pwd_session_t *session)
{
	BN_clear_free(session->private_value);
	BN_clear_free(session->peer_scalar);
	BN_clear_free(session->my_scalar);
	BN_clear_free(session->k);
	EC_POINT_clear_free(session->my_element);
	EC_POINT_clear_free(session->peer_element);
	EC_GROUP_free(session->group);
	EC_POINT_clear_free(session->pwe);
	BN_clear_free(session->order);
	BN_clear_free(session->prime);

	return 0;
}