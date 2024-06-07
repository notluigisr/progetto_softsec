ldns_rdf2buffer_str_hex(ldns_buffer *output, const ldns_rdf *rdf)
{
	size_t i;
	for (i = 0; i < ldns_rdf_size(rdf); i++) {
		ldns_buffer_printf(output, "STR", ldns_rdf_data(rdf)[i]);
	}

	return ldns_buffer_status(output);
}