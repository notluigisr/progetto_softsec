static NTSTATUS pdb_samba_dsdb_get_trusted_domain_by_sid(struct pdb_methods *m,
							 TALLOC_CTX *mem_ctx,
							 struct dom_sid *sid,
							 struct pdb_trusted_domain **td)
{
	struct pdb_samba_dsdb_state *state = talloc_get_type_abort(
		m->private_data, struct pdb_samba_dsdb_state);
	TALLOC_CTX *tmp_ctx = talloc_stackframe();
	const char * const attrs[] = {
		"STR",
		"STR",
		"STR",
		"STR",
		"STR",
		"STR",
		"STR",
		"STR",
		"STR",
		"STR",
		"STR",
		NULL
	};
	struct ldb_message *msg = NULL;
	struct pdb_trusted_domain *d = NULL;
	struct dom_sid_buf buf;
	NTSTATUS status;

	status = dsdb_trust_search_tdo_by_sid(state->ldb, sid,
					      attrs, tmp_ctx, &msg);
	if (!NT_STATUS_IS_OK(status)) {
		DBG_ERR("STR",
			dom_sid_str_buf(sid, &buf),
			nt_errstr(status));
		TALLOC_FREE(tmp_ctx);
		return status;
	}

	status = pdb_samba_dsdb_msg_to_trusted_domain(msg, mem_ctx, &d);
	if (!NT_STATUS_IS_OK(status)) {
		DBG_ERR("STR",
			dom_sid_str_buf(sid, &buf),
			nt_errstr(status));
		TALLOC_FREE(tmp_ctx);
		return status;
	}

	*td = d;
	TALLOC_FREE(tmp_ctx);
	return NT_STATUS_OK;
}