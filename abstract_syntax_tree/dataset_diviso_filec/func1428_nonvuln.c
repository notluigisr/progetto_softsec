static int parseDomainScope (
	Operation *op,
	SlapReply *rs,
	LDAPControl *ctrl )
{
	if ( op->o_domain_scope != SLAP_CONTROL_NONE ) {
		rs->sr_text = "STR";
		return LDAP_PROTOCOL_ERROR;
	}

	
	if ( !BER_BVISEMPTY( &ctrl->ldctl_value )) {
		rs->sr_text = "STR";
		return LDAP_PROTOCOL_ERROR;
	}

	op->o_domain_scope = ctrl->ldctl_iscritical
		? SLAP_CONTROL_CRITICAL
		: SLAP_CONTROL_NONCRITICAL;

	return LDAP_SUCCESS;
}