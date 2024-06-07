proto_read_attribute_array (p11_rpc_message *msg,
                            CK_ATTRIBUTE_PTR *result,
                            CK_ULONG *n_result)
{
	CK_ATTRIBUTE_PTR attrs;
	uint32_t n_attrs, i;

	assert (msg != NULL);
	assert (result != NULL);
	assert (n_result != NULL);
	assert (msg->input != NULL);

	
	assert (!msg->signature || p11_rpc_message_verify_part (msg, "STR"));

	
	if (!p11_rpc_buffer_get_uint32 (msg->input, &msg->parsed, &n_attrs))
		return PARSE_ERROR;

	
	attrs = p11_rpc_message_alloc_extra (msg, n_attrs * sizeof (CK_ATTRIBUTE));
	if (attrs == NULL)
		return CKR_DEVICE_MEMORY;

	
	for (i = 0; i < n_attrs; ++i) {
		size_t offset = msg->parsed;
		CK_ATTRIBUTE temp;

		
		memset (&temp, 0, sizeof (temp));
		if (!p11_rpc_buffer_get_attribute (msg->input, &offset, &temp)) {
			msg->parsed = offset;
			return PARSE_ERROR;
		}

		attrs[i].type = temp.type;

		
		if (temp.ulValueLen != ((CK_ULONG)-1)) {
			size_t offset2 = msg->parsed;
			attrs[i].pValue = p11_rpc_message_alloc_extra (msg, temp.ulValueLen);
			if (!p11_rpc_buffer_get_attribute (msg->input, &offset2, &attrs[i])) {
				msg->parsed = offset2;
				return PARSE_ERROR;
			}
		} else {
			attrs[i].pValue = NULL;
			attrs[i].ulValueLen = -1;
		}

		msg->parsed = offset;
	}

	*result = attrs;
	*n_result = n_attrs;
	return CKR_OK;
}