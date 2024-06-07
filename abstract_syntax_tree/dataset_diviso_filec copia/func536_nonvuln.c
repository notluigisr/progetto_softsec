forward_request(struct module_qstate* qstate, struct iter_qstate* iq)
{
	struct delegpt* dp;
	uint8_t* delname = iq->qchase.qname;
	size_t delnamelen = iq->qchase.qname_len;
	if(iq->refetch_glue && iq->dp) {
		delname = iq->dp->name;
		delnamelen = iq->dp->namelen;
	}
	
	if( (iq->qchase.qtype == LDNS_RR_TYPE_DS || iq->refetch_glue)
		&& !dname_is_root(iq->qchase.qname))
		dname_remove_label(&delname, &delnamelen);
	dp = forwards_lookup(qstate->env->fwds, delname, iq->qchase.qclass);
	if(!dp) 
		return 0;
	
	iq->chase_flags |= BIT_RD; 
	iq->dp = delegpt_copy(dp, qstate->region);
	
	verbose(VERB_ALGO, "STR");
	return 1;
}