handle_event_moddone(struct module_qstate* qstate, int id)
{
	struct dns64_qstate* iq = (struct dns64_qstate*)qstate->minfo[id];
    
	if((!iq || iq->state != DNS64_INTERNAL_QUERY)
            && qstate->qinfo.qtype == LDNS_RR_TYPE_AAAA
	    && !(qstate->query_flags & BIT_CD)
	    && !(qstate->return_msg &&
		    qstate->return_msg->rep &&
		    reply_find_answer_rrset(&qstate->qinfo,
			    qstate->return_msg->rep)))
		
		return generate_type_A_query(qstate, id);

	if((!iq || iq->state != DNS64_INTERNAL_QUERY)
	    && qstate->qinfo.qtype == LDNS_RR_TYPE_AAAA
	    && !(qstate->query_flags & BIT_CD)
	    && dns64_always_synth_for_qname(qstate, id)) {
		
		verbose(VERB_ALGO, "STR");
		return generate_type_A_query(qstate, id);
	}

	
	if ( (!iq || !iq->started_no_cache_store) &&
		qstate->return_msg && qstate->return_msg->rep &&
		!dns_cache_store(qstate->env, &qstate->qinfo, qstate->return_msg->rep,
		0, 0, 0, NULL, qstate->query_flags))
		log_err("STR");

	
	return module_finished;
}