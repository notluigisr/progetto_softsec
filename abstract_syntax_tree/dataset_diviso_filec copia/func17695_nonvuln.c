ldns_rdf2buffer_str_time(ldns_buffer *output, const ldns_rdf *rdf)
{
	
	struct tm tm;
	char date_buf[16];

	memset(&tm, 0, sizeof(tm));
	if (ldns_serial_arithmitics_gmtime_r(ldns_rdf2native_int32(rdf), time(NULL), &tm)
	    && strftime(date_buf, 15, "STR", &tm)) {
		ldns_buffer_printf(output, "STR", date_buf);
	}
	return ldns_buffer_status(output);
}