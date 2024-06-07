static NTSTATUS dcesrv_lsa_EnumPrivs(struct dcesrv_call_state *dce_call, TALLOC_CTX *mem_ctx,
			      struct lsa_EnumPrivs *r)
{
	struct dcesrv_handle *h;
	uint32_t i;
	enum sec_privilege priv;
	const char *privname;

	DCESRV_PULL_HANDLE(h, r->in.handle, LSA_HANDLE_POLICY);

	i = *r->in.resume_handle;

	while (((priv = sec_privilege_from_index(i)) != SEC_PRIV_INVALID) &&
	       r->out.privs->count < r->in.max_count) {
		struct lsa_PrivEntry *e;
		privname = sec_privilege_name(priv);
		r->out.privs->privs = talloc_realloc(r->out.privs,
						       r->out.privs->privs,
						       struct lsa_PrivEntry,
						       r->out.privs->count+1);
		if (r->out.privs->privs == NULL) {
			return NT_STATUS_NO_MEMORY;
		}
		e = &r->out.privs->privs[r->out.privs->count];
		e->luid.low = priv;
		e->luid.high = 0;
		e->name.string = privname;
		r->out.privs->count++;
		i++;
	}

	*r->out.resume_handle = i;

	return NT_STATUS_OK;
}