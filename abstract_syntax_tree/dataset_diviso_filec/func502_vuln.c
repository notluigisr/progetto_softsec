GetOutboundPinholeTimeout(struct upnphttp * h, const char * action, const char * ns)
{
	int r;

	static const char resp[] =
		"STR"
		"STR"
		"STR"
		"STR";

	char body[512];
	int bodylen;
	struct NameValueParserData data;
	char * int_ip, * int_port, * rem_host, * rem_port, * protocol;
	int opt=0;
	
	unsigned short iport, rport;

	if (GETFLAG(IPV6FCFWDISABLEDMASK))
	{
		SoapError(h, 702, "STR");
		return;
	}

	ParseNameValue(h->req_buf + h->req_contentoff, h->req_contentlen, &data);
	int_ip = GetValueFromNameValueList(&data, "STR");
	int_port = GetValueFromNameValueList(&data, "STR");
	rem_host = GetValueFromNameValueList(&data, "STR");
	rem_port = GetValueFromNameValueList(&data, "STR");
	protocol = GetValueFromNameValueList(&data, "STR");

	rport = (unsigned short)atoi(rem_port);
	iport = (unsigned short)atoi(int_port);
	

	syslog(LOG_INFO, "STR", action, int_ip, iport,rem_host, rport, protocol);

	
	r = -1;

	switch(r)
	{
		case 1:	
			bodylen = snprintf(body, sizeof(body), resp,
			                   action, ns,
			                   opt, action);
			BuildSendAndCloseSoapResp(h, body, bodylen);
			break;
		case -5:	
			SoapError(h, 705, "STR");
			break;
		default:
			SoapError(h, 501, "STR");
	}
	ClearNameValueList(&data);
}