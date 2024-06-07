synth_cname(uint8_t* qname, size_t qnamelen, struct rrset_parse* dname_rrset, 
	uint8_t* alias, size_t* aliaslen, sldns_buffer* pkt)
{
	
	uint8_t* dtarg = NULL;
	size_t dtarglen;
	if(!parse_get_cname_target(dname_rrset, &dtarg, &dtarglen))
		return 0; 
	log_assert(qnamelen > dname_rrset->dname_len);
	
	
	*aliaslen = qnamelen + dtarglen - dname_rrset->dname_len;
	if(*aliaslen > LDNS_MAX_DOMAINLEN)
		return 0; 
	
	dname_pkt_copy(pkt, alias, qname);
	dname_pkt_copy(pkt, alias+(qnamelen-dname_rrset->dname_len), dtarg);
	return 1;
}