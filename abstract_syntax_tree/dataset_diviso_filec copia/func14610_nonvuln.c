static NTSTATUS pdb_init_samba_dsdb(struct pdb_methods **pdb_method,
			     const char *location)
{
	struct pdb_methods *m;
	struct pdb_samba_dsdb_state *state;
	NTSTATUS status;
	char *errstring = NULL;
	int ret;

	if ( !NT_STATUS_IS_OK(status = make_pdb_method( &m )) ) {
		return status;
	}

	state = talloc_zero(m, struct pdb_samba_dsdb_state);
	if (state == NULL) {
		goto nomem;
	}
	m->private_data = state;
	m->free_private_data = free_private_data;
	pdb_samba_dsdb_init_methods(m);

	state->ev = s4_event_context_init(state);
	if (!state->ev) {
		DEBUG(0, ("STR"));
		goto nomem;
	}

	state->lp_ctx = loadparm_init_s3(state, loadparm_s3_helpers());
	if (state->lp_ctx == NULL) {
		DEBUG(0, ("STR"));
		goto nomem;
	}

	if (location == NULL) {
		location = "STR";
	}

	ret = samdb_connect_url(state,
				state->ev,
				state->lp_ctx,
				system_session(state->lp_ctx),
				0,
				location,
				NULL,
				&state->ldb,
				&errstring);

	if (!state->ldb) {
		DEBUG(0, ("STR",
			  errstring, ldb_strerror(ret)));
		status = NT_STATUS_INTERNAL_ERROR;
		goto fail;
	}

	state->idmap_ctx = idmap_init(state, state->ev,
				      state->lp_ctx);
	if (!state->idmap_ctx) {
		DEBUG(0, ("STR"));
		status = NT_STATUS_INTERNAL_ERROR;
		goto fail;
	}

	status = pdb_samba_dsdb_init_secrets(m);
	if (!NT_STATUS_IS_OK(status)) {
		DEBUG(10, ("STR"));
		goto fail;
	}

	*pdb_method = m;
	return NT_STATUS_OK;
nomem:
	status = NT_STATUS_NO_MEMORY;
fail:
	TALLOC_FREE(m);
	return status;
}