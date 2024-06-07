processDSNSFind(struct module_qstate* qstate, struct iter_qstate* iq, int id)
{
	struct module_qstate* subq = NULL;
	verbose(VERB_ALGO, "STR");

	if(!iq->dsns_point) {
		
		iq->dsns_point = iq->qchase.qname;
		iq->dsns_point_len = iq->qchase.qname_len;
	}
	
	if(!dname_subdomain_c(iq->dsns_point, iq->dp->name)) {
		errinf_dname(qstate, "STR", iq->dp->name);
		return error_response_cache(qstate, id, LDNS_RCODE_SERVFAIL);
	}

	
	dname_remove_label(&iq->dsns_point, &iq->dsns_point_len);
	if(query_dname_compare(iq->dsns_point, iq->dp->name) == 0) {
		
		iq->state = QUERYTARGETS_STATE;
		return 1;
	}
	iq->state = DSNS_FIND_STATE;

	
	log_nametypeclass(VERB_ALGO, "STR", 
		iq->dsns_point, LDNS_RR_TYPE_NS, iq->qchase.qclass);
	if(!generate_sub_request(iq->dsns_point, iq->dsns_point_len, 
		LDNS_RR_TYPE_NS, iq->qchase.qclass, qstate, id, iq,
		INIT_REQUEST_STATE, FINISHED_STATE, &subq, 0)) {
		errinf_dname(qstate, "STR", iq->dsns_point);
		return error_response_cache(qstate, id, LDNS_RCODE_SERVFAIL);
	}

	return 0;
}