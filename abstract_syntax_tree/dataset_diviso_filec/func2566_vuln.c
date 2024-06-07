processPrimeResponse(struct module_qstate* qstate, int id)
{
	struct iter_qstate* iq = (struct iter_qstate*)qstate->minfo[id];
	enum response_type type;
	iq->response->rep->flags &= ~(BIT_RD|BIT_RA); 
	type = response_type_from_server(
		(int)((iq->chase_flags&BIT_RD) || iq->chase_to_rd), 
		iq->response, &iq->qchase, iq->dp);
	if(type == RESPONSE_TYPE_ANSWER) {
		qstate->return_rcode = LDNS_RCODE_NOERROR;
		qstate->return_msg = iq->response;
	} else {
		errinf(qstate, "STR");
		errinf_dname(qstate, "STR", qstate->qinfo.qname);
		qstate->return_rcode = LDNS_RCODE_SERVFAIL;
		qstate->return_msg = NULL;
	}

	
	if(qstate->env->cfg->harden_referral_path) {
		struct module_qstate* subq = NULL;
		log_nametypeclass(VERB_ALGO, "STR", 
			qstate->qinfo.qname, qstate->qinfo.qtype,
			qstate->qinfo.qclass);
		if(!generate_sub_request(qstate->qinfo.qname, 
			qstate->qinfo.qname_len, qstate->qinfo.qtype,
			qstate->qinfo.qclass, qstate, id, iq,
			INIT_REQUEST_STATE, FINISHED_STATE, &subq, 1)) {
			verbose(VERB_ALGO, "STR");
		}
		generate_a_aaaa_check(qstate, iq, id);
	}

	
	qstate->ext_state[id] = module_finished;
	return 0;
}