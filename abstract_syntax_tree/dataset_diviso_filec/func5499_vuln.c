ldns_rdf2buffer_str_str(ldns_buffer *output, const ldns_rdf *rdf)
{
	const uint8_t *data = ldns_rdf_data(rdf);
	uint8_t length = data[0];
	size_t i;

	ldns_buffer_printf(output, "STR");
	for (i = 1; i <= length; ++i) {
		char ch = (char) data[i];
		if (isprint((int)ch) || ch=='\t') {
			if (ch=='\"'||ch=='\\')
				ldns_buffer_printf(output, "STR", ch);
			else
				ldns_buffer_printf(output, "STR", ch);
		} else {
			ldns_buffer_printf(output, "STR",
                                (unsigned)(uint8_t) ch);
		}
	}
	ldns_buffer_printf(output, "STR");
	return ldns_buffer_status(output);
}