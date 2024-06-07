static NTSTATUS dcesrv_lsa_OpenTrustedDomainByName(struct dcesrv_call_state *dce_call,
					    TALLOC_CTX *mem_ctx,
					    struct lsa_OpenTrustedDomainByName *r)
{
	struct dcesrv_handle *policy_handle;
	struct lsa_policy_state *policy_state;
	struct dcesrv_handle *handle;
	char *td_name;
	char *filter;
	NTSTATUS status;

	DCESRV_PULL_HANDLE(policy_handle, r->in.handle, LSA_HANDLE_POLICY);
	ZERO_STRUCTP(r->out.trustdom_handle);
	policy_state = policy_handle->data;

	if (!r->in.name.string) {
		return NT_STATUS_INVALID_PARAMETER;
	}

	
	td_name = ldb_binary_encode_string(mem_ctx, r->in.name.string);
	if (td_name == NULL) {
		return NT_STATUS_NO_MEMORY;
	}

	filter = talloc_asprintf(mem_ctx,
			   "STR"
			     "STR",
			   td_name, td_name, td_name);
	if (filter == NULL) {
		return NT_STATUS_NO_MEMORY;
	}

	status = dcesrv_lsa_OpenTrustedDomain_common(dce_call, mem_ctx,
						     policy_state,
						     filter,
						     r->in.access_mask,
						     &handle);
	if (!NT_STATUS_IS_OK(status)) {
		return status;
	}

	*r->out.trustdom_handle = handle->wire_handle;

	return NT_STATUS_OK;
}