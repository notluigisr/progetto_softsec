GetSpecificPortMappingEntry(struct upnphttp * h, const char * action, const char * ns)
{
	int r;

	static const char resp[] =
		"STR"
		"STR"
		"STR"
		"STR"
		"STR"
		"STR"
		"STR"
		"STR";

	char body[1024];
	int bodylen;
	struct NameValueParserData data;
	const char * r_host, * ext_port, * protocol;
	unsigned short eport, iport;
	char int_ip[32];
	char desc[64];
	unsigned int leaseduration = 0;

	ParseNameValue(h->req_buf + h->req_contentoff, h->req_contentlen, &data);
	r_host = GetValueFromNameValueList(&data, "STR");
	ext_port = GetValueFromNameValueList(&data, "STR");
	protocol = GetValueFromNameValueList(&data, "STR");

#ifdef UPNP_STRICT
	if(!ext_port || !protocol || !r_host)
#else
	if(!ext_port || !protocol)
#endif
	{
		ClearNameValueList(&data);
		SoapError(h, 402, "STR");
		return;
	}
#ifndef SUPPORT_REMOTEHOST
#ifdef UPNP_STRICT
	if (r_host && (r_host[0] != '\0') && (0 != strcmp(r_host, "STR")))
	{
		ClearNameValueList(&data);
		SoapError(h, 726, "STR");
		return;
	}
#endif
#endif

	eport = (unsigned short)atoi(ext_port);
	if(eport == 0)
	{
		ClearNameValueList(&data);
		SoapError(h, 402, "STR");
		return;
	}

	
	r = upnp_get_redirection_infos(eport, protocol, &iport,
	                               int_ip, sizeof(int_ip),
	                               desc, sizeof(desc),
	                               NULL, 0,
	                               &leaseduration);

	if(r < 0)
	{
		SoapError(h, 714, "STR");
	}
	else
	{
		syslog(LOG_INFO, "STR",
		       action,
		       r_host ? r_host : "STR", ext_port, protocol, int_ip,
		       (unsigned int)iport, desc);
		bodylen = snprintf(body, sizeof(body), resp,
				action, ns,
				(unsigned int)iport, int_ip, desc, leaseduration,
				action);
		BuildSendAndCloseSoapResp(h, body, bodylen);
	}

	ClearNameValueList(&data);
}