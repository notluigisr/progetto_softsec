void credssp_send(rdpCredssp* credssp)
{
	wStream* s;
	int length;
	int ts_request_length;
	int nego_tokens_length;
	int pub_key_auth_length;
	int auth_info_length;

	nego_tokens_length = (credssp->negoToken.cbBuffer > 0) ? credssp_sizeof_nego_tokens(credssp->negoToken.cbBuffer) : 0;
	pub_key_auth_length = (credssp->pubKeyAuth.cbBuffer > 0) ? credssp_sizeof_pub_key_auth(credssp->pubKeyAuth.cbBuffer) : 0;
	auth_info_length = (credssp->authInfo.cbBuffer > 0) ? credssp_sizeof_auth_info(credssp->authInfo.cbBuffer) : 0;

	length = nego_tokens_length + pub_key_auth_length + auth_info_length;

	ts_request_length = credssp_sizeof_ts_request(length);

	s = Stream_New(NULL, ber_sizeof_sequence(ts_request_length));

	
	ber_write_sequence_tag(s, ts_request_length); 

	
	ber_write_contextual_tag(s, 0, 3, TRUE);
	ber_write_integer(s, 2); 

	
	if (nego_tokens_length > 0)
	{
		length = nego_tokens_length;

		length -= ber_write_contextual_tag(s, 1, ber_sizeof_sequence(ber_sizeof_sequence(ber_sizeof_sequence_octet_string(credssp->negoToken.cbBuffer))), TRUE); 
		length -= ber_write_sequence_tag(s, ber_sizeof_sequence(ber_sizeof_sequence_octet_string(credssp->negoToken.cbBuffer))); 
		length -= ber_write_sequence_tag(s, ber_sizeof_sequence_octet_string(credssp->negoToken.cbBuffer)); 
		length -= ber_write_sequence_octet_string(s, 0, (BYTE*) credssp->negoToken.pvBuffer, credssp->negoToken.cbBuffer); 
	}

	
	if (auth_info_length > 0)
	{
		length = auth_info_length;
		length -= ber_write_sequence_octet_string(s, 2, credssp->authInfo.pvBuffer, credssp->authInfo.cbBuffer);
	}

	
	if (pub_key_auth_length > 0)
	{
		length = pub_key_auth_length;
		length -= ber_write_sequence_octet_string(s, 3, credssp->pubKeyAuth.pvBuffer, credssp->pubKeyAuth.cbBuffer);
	}

	transport_write(credssp->transport, s);
	Stream_Free(s, TRUE);
}