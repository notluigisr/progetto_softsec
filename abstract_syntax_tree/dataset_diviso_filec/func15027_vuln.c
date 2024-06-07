processCollectClass(struct module_qstate* qstate, int id)
{
	struct iter_qstate* iq = (struct iter_qstate*)qstate->minfo[id];
	struct module_qstate* subq;
	
	if(iq->qchase.qclass == 0) {
		uint16_t c = 0;
		iq->qchase.qclass = LDNS_RR_CLASS_ANY;
		while(iter_get_next_root(qstate->env->hints,
			qstate->env->fwds, &c)) {
			
			log_nametypeclass(VERB_ALGO, "STR",
				qstate->qinfo.qname, qstate->qinfo.qtype, c);
			if(!generate_sub_request(qstate->qinfo.qname,
				qstate->qinfo.qname_len, qstate->qinfo.qtype,
				c, qstate, id, iq, INIT_REQUEST_STATE,
				FINISHED_STATE, &subq, 
				(int)!(qstate->query_flags&BIT_CD))) {
				errinf(qstate, "STR"
					"STR");
				return error_response(qstate, id, 
					LDNS_RCODE_SERVFAIL);
			}
			
			iq->num_current_queries ++;
			if(c == 0xffff)
				break;
			else c++;
		}
		
		if(iq->num_current_queries == 0) {
			verbose(VERB_ALGO, "STR"
				"STR");
			return error_response(qstate, id, LDNS_RCODE_REFUSED);
		}
		
	}
	
	return 0;
}