void ntlm_print_message_fields(NTLM_MESSAGE_FIELDS* fields, const char* name)
{
	WLog_DBG(TAG, "STR",
	         name, fields->Len, fields->MaxLen, fields->BufferOffset);

	if (fields->Len > 0)
		winpr_HexDump(TAG, WLOG_DEBUG, fields->Buffer, fields->Len);
}