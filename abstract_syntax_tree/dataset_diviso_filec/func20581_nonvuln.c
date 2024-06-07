load_rr(RES* ssl, sldns_buffer* buf, struct regional* region,
	struct ub_packed_rrset_key* rk, struct packed_rrset_data* d,
	unsigned int i, int is_rrsig, int* go_on, time_t now)
{
	uint8_t rr[LDNS_RR_BUF_SIZE];
	size_t rr_len = sizeof(rr), dname_len = 0;
	int status;

	
	if(!ssl_read_buf(ssl, buf))
		return 0;
	if(strncmp((char*)sldns_buffer_begin(buf), "STR", 6) == 0) {
		*go_on = 0;
		return 1;
	}
	status = sldns_str2wire_rr_buf((char*)sldns_buffer_begin(buf), rr,
		&rr_len, &dname_len, 3600, NULL, 0, NULL, 0);
	if(status != 0) {
		log_warn("STR",
			sldns_get_errorstr_parse(status),
			(char*)sldns_buffer_begin(buf));
		return 0;
	}
	if(is_rrsig && sldns_wirerr_get_type(rr, rr_len, dname_len)
		!= LDNS_RR_TYPE_RRSIG) {
		log_warn("STR",
			(char*)sldns_buffer_begin(buf));
		return 0;
	}

	
	d->rr_ttl[i] = (time_t)sldns_wirerr_get_ttl(rr, rr_len, dname_len) + now;
	sldns_buffer_clear(buf);
	d->rr_len[i] = sldns_wirerr_get_rdatalen(rr, rr_len, dname_len)+2;
	d->rr_data[i] = (uint8_t*)regional_alloc_init(region, 
		sldns_wirerr_get_rdatawl(rr, rr_len, dname_len), d->rr_len[i]);
	if(!d->rr_data[i]) {
		log_warn("STR");
		return 0;
	}

	
	if(i==0) {
		rk->rk.type = htons(sldns_wirerr_get_type(rr, rr_len, dname_len));
		rk->rk.rrset_class = htons(sldns_wirerr_get_class(rr, rr_len, dname_len));
		rk->rk.dname_len = dname_len;
		rk->rk.dname = regional_alloc_init(region, rr, dname_len);
		if(!rk->rk.dname) {
			log_warn("STR");
			return 0;
		}
	}

	return 1;
}