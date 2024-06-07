static bool _ber_read_OID_String_impl(TALLOC_CTX *mem_ctx, DATA_BLOB blob,
				      char **OID, size_t *bytes_eaten)
{
	int i;
	uint8_t *b;
	unsigned int v;
	char *tmp_oid = NULL;

	if (blob.length < 2) return false;

	b = blob.data;

	tmp_oid = talloc_asprintf(mem_ctx, "STR",  b[0]/40);
	if (!tmp_oid) goto nomem;
	tmp_oid = talloc_asprintf_append_buffer(tmp_oid, "STR",  b[0]%40);
	if (!tmp_oid) goto nomem;

	if (bytes_eaten != NULL) {
		*bytes_eaten = 0;
	}

	for(i = 1, v = 0; i < blob.length; i++) {
		v = (v<<7) | (b[i]&0x7f);
		if ( ! (b[i] & 0x80)) {
			tmp_oid = talloc_asprintf_append_buffer(tmp_oid, "STR",  v);
			v = 0;
			if (bytes_eaten)
				*bytes_eaten = i+1;
		}
		if (!tmp_oid) goto nomem;
	}

	*OID = tmp_oid;
	return true;

nomem:
	return false;
}