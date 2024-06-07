error_supers(struct module_qstate* qstate, int id, struct module_qstate* super)
{
	struct iter_env* ie = (struct iter_env*)qstate->env->modinfo[id];
	struct iter_qstate* super_iq = (struct iter_qstate*)super->minfo[id];

	if(qstate->qinfo.qtype == LDNS_RR_TYPE_A ||
		qstate->qinfo.qtype == LDNS_RR_TYPE_AAAA) {
		
		struct delegpt_ns* dpns = NULL;
		super_iq->num_target_queries--; 
		if(super_iq->dp)
			dpns = delegpt_find_ns(super_iq->dp, 
				qstate->qinfo.qname, qstate->qinfo.qname_len);
		if(!dpns) {
			
			
			verbose(VERB_ALGO, "STR");
			log_query_info(VERB_ALGO, "STR", &super->qinfo);
			return;
		} else {
			
			if(!cache_fill_missing(super->env, super_iq->qchase.qclass,
				super->region, super_iq->dp))
				log_err("STR");
		}
		delegpt_mark_neg(dpns, qstate->qinfo.qtype);
		dpns->resolved = 1; 
		if((dpns->got4 == 2 || !ie->supports_ipv4) &&
			(dpns->got6 == 2 || !ie->supports_ipv6))
			target_count_increase_nx(super_iq, 1);
	}
	if(qstate->qinfo.qtype == LDNS_RR_TYPE_NS) {
		
		super_iq->dp = NULL;
	}
	
	super_iq->state = QUERYTARGETS_STATE; 
	
}