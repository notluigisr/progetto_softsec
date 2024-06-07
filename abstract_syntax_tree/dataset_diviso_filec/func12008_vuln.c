proto_read_attribute_buffer (p11_rpc_message *msg,
                             CK_ATTRIBUTE_PTR *result,
                             CK_ULONG *n_result)
{
	CK_ATTRIBUTE_PTR attrs;
	uint32_t n_attrs, i;
	uint32_t value;

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

		
		if (!p11_rpc_buffer_get_uint32 (msg->input, &msg->parsed, &value))
			return PARSE_ERROR;

		attrs[i].type = value;

		
		if (!p11_rpc_buffer_get_uint32 (msg->input, &msg->parsed, &value))
			return PARSE_ERROR;

		if (value == 0) {
			attrs[i].pValue = NULL;
			attrs[i].ulValueLen = 0;
		} else {
			attrs[i].pValue = p11_rpc_message_alloc_extra (msg, value);
			if (!attrs[i].pValue)
				return CKR_DEVICE_MEMORY;
			attrs[i].ulValueLen = value;
		}
	}

	*result = attrs;
	*n_result = n_attrs;
	return CKR_OK;
}