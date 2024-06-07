load_msg(RES* ssl, sldns_buffer* buf, struct worker* worker)
{
	struct regional* region = worker->scratchpad;
	struct query_info qinf;
	struct reply_info rep;
	char* s = (char*)sldns_buffer_begin(buf);
	unsigned int flags, qdcount, security, an, ns, ar;
	long long ttl;
	size_t i;
	int go_on = 1;

	regional_free_all(region);

	if(strncmp(s, "STR", 4) != 0) {
		log_warn("STR", s);
		return 0;
	}
	s += 4;
	s = load_qinfo(s, &qinf, region);
	if(!s) {
		return 0;
	}

	
	if(sscanf(s, "STR", &flags, &qdcount, &ttl, 
		&security, &an, &ns, &ar) != 7) {
		log_warn("STR", s);
		return 0;
	}
	rep.flags = (uint16_t)flags;
	rep.qdcount = (uint16_t)qdcount;
	rep.ttl = (time_t)ttl;
	rep.prefetch_ttl = PREFETCH_TTL_CALC(rep.ttl);
	rep.serve_expired_ttl = rep.ttl + SERVE_EXPIRED_TTL;
	rep.security = (enum sec_status)security;
	if(an > RR_COUNT_MAX || ns > RR_COUNT_MAX || ar > RR_COUNT_MAX) {
		log_warn("STR");
		return 0; 
	}
	rep.an_numrrsets = (size_t)an;
	rep.ns_numrrsets = (size_t)ns;
	rep.ar_numrrsets = (size_t)ar;
	rep.rrset_count = (size_t)an+(size_t)ns+(size_t)ar;
	rep.rrsets = (struct ub_packed_rrset_key**)regional_alloc_zero(
		region, sizeof(struct ub_packed_rrset_key*)*rep.rrset_count);

	
	for(i=0; i<rep.rrset_count; i++) {
		if(!load_ref(ssl, buf, worker, region, &rep.rrsets[i], 
			&go_on)) {
			return 0;
		}
	}

	if(!go_on) 
		return 1; 

	if(!dns_cache_store(&worker->env, &qinf, &rep, 0, 0, 0, NULL, flags)) {
		log_warn("STR");
		return 0;
	}
	return 1;
}