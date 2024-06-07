ldns_pkt_cert_algorithm2str(ldns_cert_algorithm cert_algorithm)
{
	char *str;
	ldns_buffer *buf;

	buf = ldns_buffer_new(10);
	if (!buf) {
		return NULL;
	}

	str = NULL;
	if (ldns_cert_algorithm2buffer_str(buf, cert_algorithm)
	    == LDNS_STATUS_OK) {
		str = ldns_buffer_export2str(buf);
	}

	ldns_buffer_free(buf);
	return str;
}