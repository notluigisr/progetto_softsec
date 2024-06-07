processFinished(struct module_qstate* qstate, struct iter_qstate* iq,
	int id)
{
	log_query_info(VERB_QUERY, "STR", 
		&qstate->qinfo);

	
	if(!qstate->no_cache_store && iq->query_for_pside_glue
		&& !iq->pside_glue)
			iter_store_parentside_neg(qstate->env, &qstate->qinfo,
				iq->deleg_msg?iq->deleg_msg->rep:
				(iq->response?iq->response->rep:NULL));
	if(!iq->response) {
		verbose(VERB_ALGO, "STR");
		errinf(qstate, "STR");
		return error_response(qstate, id, LDNS_RCODE_SERVFAIL);
	}

	
	iq->response->rep->flags |= BIT_RA;

	
	
	iq->response->rep->flags &= ~BIT_AA;

	
	iq->response->rep->flags |= BIT_QR;

	
	qstate->ext_state[id] = module_finished;

	
	

	
	if(iq->an_prepend_list || iq->ns_prepend_list) {
		if(!iter_prepend(iq, iq->response, qstate->region)) {
			log_err("STR");
			return error_response(qstate, id, LDNS_RCODE_SERVFAIL);
		}
		
		iq->response->qinfo = qstate->qinfo;
		
		iq->response->rep->security = sec_status_unchecked;
		
		if(!qstate->no_cache_store && qstate->query_flags&BIT_RD) {
			iter_dns_store(qstate->env, &qstate->qinfo, 
				iq->response->rep, 0, qstate->prefetch_leeway,
				iq->dp&&iq->dp->has_parent_side_NS,
				qstate->region, qstate->query_flags);
		}
	}
	qstate->return_rcode = LDNS_RCODE_NOERROR;
	qstate->return_msg = iq->response;
	return 0;
}