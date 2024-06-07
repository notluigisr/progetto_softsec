SEC_WINNT_AUTH_IDENTITY* nla_get_identity(rdpNla* nla)
{
	if (!nla)
		return NULL;

	return nla->identity;
}