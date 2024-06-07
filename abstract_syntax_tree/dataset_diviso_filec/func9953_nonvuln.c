proto_write_token_info (p11_rpc_message *msg,
                        CK_TOKEN_INFO_PTR info)
{
	assert (msg != NULL);
	assert (info != NULL);

	if (!p11_rpc_message_write_space_string (msg, info->label, 32) ||
	    !p11_rpc_message_write_space_string (msg, info->manufacturerID, 32) ||
	    !p11_rpc_message_write_space_string (msg, info->model, 16) ||
	    !p11_rpc_message_write_space_string (msg, info->serialNumber, 16) ||
	    !p11_rpc_message_write_ulong (msg, info->flags) ||
	    !p11_rpc_message_write_ulong (msg, info->ulMaxSessionCount) ||
	    !p11_rpc_message_write_ulong (msg, info->ulSessionCount) ||
	    !p11_rpc_message_write_ulong (msg, info->ulMaxRwSessionCount) ||
	    !p11_rpc_message_write_ulong (msg, info->ulRwSessionCount) ||
	    !p11_rpc_message_write_ulong (msg, info->ulMaxPinLen) ||
	    !p11_rpc_message_write_ulong (msg, info->ulMinPinLen) ||
	    !p11_rpc_message_write_ulong (msg, info->ulTotalPublicMemory) ||
	    !p11_rpc_message_write_ulong (msg, info->ulFreePublicMemory) ||
	    !p11_rpc_message_write_ulong (msg, info->ulTotalPrivateMemory) ||
	    !p11_rpc_message_write_ulong (msg, info->ulFreePrivateMemory) ||
	    !p11_rpc_message_write_version (msg, &info->hardwareVersion) ||
	    !p11_rpc_message_write_version (msg, &info->firmwareVersion) ||
	    !p11_rpc_message_write_space_string (msg, info->utcTime, 16))
		return PREP_ERROR;

	return CKR_OK;
}