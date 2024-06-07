DWORD nla_get_error(rdpNla* nla)
{
	if (!nla)
		return ERROR_INTERNAL_ERROR;
	return nla->errorCode;
}