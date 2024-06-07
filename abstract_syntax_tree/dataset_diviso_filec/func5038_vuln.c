void dname_pkt_copy(sldns_buffer* pkt, uint8_t* to, uint8_t* dname)
{
	
	size_t len = 0;
	uint8_t lablen;
	lablen = *dname++;
	while(lablen) {
		if(LABEL_IS_PTR(lablen)) {
			
			dname = sldns_buffer_at(pkt, PTR_OFFSET(lablen, *dname));
			lablen = *dname++;
			continue;
		}
		log_assert(lablen <= LDNS_MAX_LABELLEN);
		len += (size_t)lablen+1;
		if(len >= LDNS_MAX_DOMAINLEN) {
			*to = 0; 
			log_err("STR");
			return;
		}
		*to++ = lablen;
		memmove(to, dname, lablen);
		dname += lablen;
		to += lablen;
		lablen = *dname++;
	}
	
	*to = 0;
}