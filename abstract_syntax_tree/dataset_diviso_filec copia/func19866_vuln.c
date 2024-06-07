generate_dnskey_prefetch(struct module_qstate* qstate, 
	struct iter_qstate* iq, int id)
{
	struct module_qstate* subq;
	log_assert(iq->dp);

	
	if(qstate->qinfo.qtype == LDNS_RR_TYPE_DNSKEY &&
		query_dname_compare(iq->dp->name, qstate->qinfo.qname)==0 &&
		(qstate->query_flags&BIT_RD) && !(qstate->query_flags&BIT_CD)){
		return;
	}

	
	log_nametypeclass(VERB_ALGO, "STR", 
		iq->dp->name, LDNS_RR_TYPE_DNSKEY, iq->qchase.qclass);
	if(!generate_sub_request(iq->dp->name, iq->dp->namelen, 
		LDNS_RR_TYPE_DNSKEY, iq->qchase.qclass, qstate, id, iq,
		INIT_REQUEST_STATE, FINISHED_STATE, &subq, 0)) {
		
		verbose(VERB_ALGO, "STR");
		return;
	}
	if(subq) {
		struct iter_qstate* subiq = 
			(struct iter_qstate*)subq->minfo[id];
		
		
		subiq->dp = delegpt_copy(iq->dp, subq->region);
		
	}
}