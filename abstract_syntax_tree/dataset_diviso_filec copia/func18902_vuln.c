mcs_recv_connect_response(STREAM mcs_data)
{
	uint8 result;
	int length;
	STREAM s;

	s = iso_recv(NULL);
	if (s == NULL)
		return False;

	ber_parse_header(s, MCS_CONNECT_RESPONSE, &length);

	ber_parse_header(s, BER_TAG_RESULT, &length);
	in_uint8(s, result);
	if (result != 0)
	{
		error("STR", result);
		return False;
	}

	ber_parse_header(s, BER_TAG_INTEGER, &length);
	in_uint8s(s, length);	
	mcs_parse_domain_params(s);

	ber_parse_header(s, BER_TAG_OCTET_STRING, &length);

	sec_process_mcs_data(s);
	
	return s_check_end(s);
}