default_opaque_literal_attr(tvbuff_t *tvb, guint32 offset,
			    const char *token _U_, guint8 codepage _U_, guint32 *length)
{
	guint32 data_len = tvb_get_guintvar(tvb, offset, length);
	char *str = wmem_strdup_printf(wmem_packet_scope(), "STR", data_len);
	*length += data_len;
	return str;
}