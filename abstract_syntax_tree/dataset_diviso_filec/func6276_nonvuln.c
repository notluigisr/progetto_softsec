BOOL nla_set_sspi_module(rdpNla* nla, const char* sspiModule)
{
	if (!nla)
		return FALSE;

	if (nla->SspiModule)
	{
		free(nla->SspiModule);
		nla->SspiModule = NULL;
	}

	if (!sspiModule)
		return TRUE;

	nla->SspiModule = _strdup(sspiModule);
	if (!nla->SspiModule)
		return FALSE;

	return TRUE;
}