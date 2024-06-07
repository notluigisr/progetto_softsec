proto_read_byte_array (p11_rpc_message *msg,
                       CK_BYTE_PTR *array,
                       CK_ULONG *n_array)
{
	const unsigned char *data;
	unsigned char valid;
	size_t n_data;

	assert (msg != NULL);
	assert (msg->input != NULL);

	
	assert (!msg->signature || p11_rpc_message_verify_part (msg, "STR"));

	
	if (!p11_rpc_buffer_get_byte (msg->input, &msg->parsed, &valid))
		return PARSE_ERROR;

	if (!valid) {
		*array = NULL;
		*n_array = 0;
		return CKR_OK;
	}

	
	if (!p11_rpc_buffer_get_byte_array (msg->input, &msg->parsed, &data, &n_data))
		return PARSE_ERROR;

	*array = (CK_BYTE_PTR)data;
	*n_array = n_data;
	return CKR_OK;
}