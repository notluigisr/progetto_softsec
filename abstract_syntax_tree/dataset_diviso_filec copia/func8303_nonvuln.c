static int parseDontUseCopy (
	Operation *op,
	SlapReply *rs,
	LDAPControl *ctrl )
{
	if ( op->o_dontUseCopy != SLAP_CONTROL_NONE ) {
		rs->sr_text = "STR";
		return LDAP_PROTOCOL_ERROR;
	}

	if ( !BER_BVISNULL( &ctrl->ldctl_value )) {
		rs->sr_text = "STR";
		return LDAP_PROTOCOL_ERROR;
	}

	if ( ( global_disallows & SLAP_DISALLOW_DONTUSECOPY_N_CRIT )
		&& !ctrl->ldctl_iscritical )
	{
		rs->sr_text = "STR";
		return LDAP_PROTOCOL_ERROR;
	}

	op->o_dontUseCopy = ctrl->ldctl_iscritical
		? SLAP_CONTROL_CRITICAL
		: SLAP_CONTROL_NONCRITICAL;

	return LDAP_SUCCESS;
}