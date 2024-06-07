static bool ntlmssp_check_buffer(const struct ntlmssp_buffer *buffer,
				 size_t data_size, const char **error)
{
	uint32_t offset = read_le32(&buffer->offset);
	uint16_t length = read_le16(&buffer->length);
	uint16_t space = read_le16(&buffer->space);

	
	if (length == 0 && space == 0)
		return TRUE;

	if (offset >= data_size) {
		*error = "STR";
		return FALSE;
	}

	if (offset + space > data_size) {
		*error = "STR";
		return FALSE;
	}

	return TRUE;
}