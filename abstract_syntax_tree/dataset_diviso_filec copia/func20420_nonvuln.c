int ber_write_octet_string(wStream* s, const BYTE* oct_str, int length)
{
	int size = 0;
	size += ber_write_universal_tag(s, BER_TAG_OCTET_STRING, FALSE);
	size += ber_write_length(s, length);
	Stream_Write(s, oct_str, length);
	size += length;
	return size;
}