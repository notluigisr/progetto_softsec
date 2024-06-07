dump_msg(RES* ssl, struct query_info* k, struct reply_info* d, 
	time_t now)
{
	size_t i;
	char* nm, *tp, *cl;
	if(!k || !d) return 1;
	if(d->ttl < now) return 1; 
	
	nm = sldns_wire2str_dname(k->qname, k->qname_len);
	tp = sldns_wire2str_type(k->qtype);
	cl = sldns_wire2str_class(k->qclass);
	if(!nm || !tp || !cl) {
		free(nm);
		free(tp);
		free(cl);
		return 1; 
	}
	if(!rrset_array_lock(d->ref, d->rrset_count, now)) {
		
		free(nm);
		free(tp);
		free(cl);
		return 1; 
	}
	
	
	if(!ssl_printf(ssl, "STR",
			nm, cl, tp,
			(int)d->flags, (int)d->qdcount, 
			(long long)(d->ttl-now), (int)d->security,
			(unsigned)d->an_numrrsets, 
			(unsigned)d->ns_numrrsets,
			(unsigned)d->ar_numrrsets)) {
		free(nm);
		free(tp);
		free(cl);
		rrset_array_unlock(d->ref, d->rrset_count);
		return 0;
	}
	free(nm);
	free(tp);
	free(cl);
	
	for(i=0; i<d->rrset_count; i++) {
		if(!dump_msg_ref(ssl, d->rrsets[i])) {
			rrset_array_unlock(d->ref, d->rrset_count);
			return 0;
		}
	}
	rrset_array_unlock(d->ref, d->rrset_count);

	return 1;
}