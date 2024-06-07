static NTSTATUS dcesrv_lsa_GetUserName(struct dcesrv_call_state *dce_call, TALLOC_CTX *mem_ctx,
				struct lsa_GetUserName *r)
{
	enum dcerpc_transport_t transport =
		dcerpc_binding_get_transport(dce_call->conn->endpoint->ep_description);
	struct auth_session_info *session_info =
		dcesrv_call_session_info(dce_call);
	NTSTATUS status = NT_STATUS_OK;
	const char *account_name;
	const char *authority_name;
	struct lsa_String *_account_name;
	struct lsa_String *_authority_name = NULL;

	if (transport != NCACN_NP && transport != NCALRPC) {
		DCESRV_FAULT(DCERPC_FAULT_ACCESS_DENIED);
	}

	
	r->out.account_name = r->in.account_name;
	r->out.authority_name = r->in.authority_name;

	if (r->in.account_name
	    && *r->in.account_name
	    
	    ) {
		return NT_STATUS_INVALID_PARAMETER;
	}

	if (r->in.authority_name
	    && *r->in.authority_name
	    
	    ) {
		return NT_STATUS_INVALID_PARAMETER;
	}

	account_name = talloc_reference(mem_ctx, session_info->info->account_name);
	authority_name = talloc_reference(mem_ctx, session_info->info->domain_name);

	_account_name = talloc(mem_ctx, struct lsa_String);
	NT_STATUS_HAVE_NO_MEMORY(_account_name);
	_account_name->string = account_name;

	if (r->in.authority_name) {
		_authority_name = talloc(mem_ctx, struct lsa_String);
		NT_STATUS_HAVE_NO_MEMORY(_authority_name);
		_authority_name->string = authority_name;
	}

	*r->out.account_name = _account_name;
	if (r->out.authority_name) {
		*r->out.authority_name = _authority_name;
	}

	return status;
}