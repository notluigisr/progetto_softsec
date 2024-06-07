static int rtecp_construct_fci(sc_card_t *card, const sc_file_t *file,
		u8 *out, size_t *outlen)
{
	u8 buf[64], *p = out;

	assert(card && card->ctx && file && out && outlen);
	assert(*outlen  >=  (size_t)(p - out) + 2);
	*p++ = 0x6F; 
	p++; 

	
	buf[0] = (file->size >> 8) & 0xFF;
	buf[1] = file->size & 0xFF;
	sc_asn1_put_tag(0x80, buf, 2, p, *outlen - (p - out), &p);

	
	if (file->type_attr_len)
	{
		assert(sizeof(buf) >= file->type_attr_len);
		memcpy(buf, file->type_attr, file->type_attr_len);
		sc_asn1_put_tag(0x82, buf, file->type_attr_len,
				p, *outlen - (p - out), &p);
	}
	else
	{
		switch (file->type)
		{
		case SC_FILE_TYPE_WORKING_EF:
			buf[0] = 0x01;
			break;
		case SC_FILE_TYPE_DF:
			buf[0] = 0x38;
			break;
		case SC_FILE_TYPE_INTERNAL_EF:
		default:
			SC_FUNC_RETURN(card->ctx, SC_LOG_DEBUG_NORMAL, SC_ERROR_NOT_SUPPORTED);
		}
		buf[1] = 0;
		sc_asn1_put_tag(0x82, buf, 2, p, *outlen - (p - out), &p);
	}
	
	buf[0] = (file->id >> 8) & 0xFF;
	buf[1] = file->id & 0xFF;
	sc_asn1_put_tag(0x83, buf, 2, p, *outlen - (p - out), &p);

	if (file->prop_attr_len)
	{
		assert(sizeof(buf) >= file->prop_attr_len);
		memcpy(buf, file->prop_attr, file->prop_attr_len);
		sc_asn1_put_tag(0x85, buf, file->prop_attr_len,
				p, *outlen - (p - out), &p);
	}
	if (file->sec_attr_len)
	{
		assert(sizeof(buf) >= file->sec_attr_len);
		memcpy(buf, file->sec_attr, file->sec_attr_len);
		sc_asn1_put_tag(0x86, buf, file->sec_attr_len,
				p, *outlen - (p - out), &p);
	}
	out[1] = p - out - 2; 
	*outlen = p - out;
	SC_FUNC_RETURN(card->ctx, SC_LOG_DEBUG_VERBOSE, 0);
}