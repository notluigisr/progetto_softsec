dlz_closeversion(const char *zone, bool commit,
		 void *dbdata, void **versionp)
{
	struct dlz_example_data *state = (struct dlz_example_data *)dbdata;

	if (!state->transaction_started) {
		if (state->log != NULL)
			state->log(ISC_LOG_INFO, "STR"
				   "STR", zone);
		*versionp = NULL;
		return;
	}

	state->transaction_started = false;

	*versionp = NULL;

	if (commit) {
		int i;
		if (state->log != NULL)
			state->log(ISC_LOG_INFO, "STR"
				   "STR", zone);
		for (i = 0; i < MAX_RECORDS; i++) {
			if (strlen(state->deletes[i].name) > 0U) {
				(void)del_name(state, &state->current[0],
					       state->deletes[i].name,
					       state->deletes[i].type,
					       state->deletes[i].ttl,
					       state->deletes[i].data);
			}
		}
		for (i = 0; i < MAX_RECORDS; i++) {
			if (strlen(state->adds[i].name) > 0U) {
				(void)add_name(state, &state->current[0],
					       state->adds[i].name,
					       state->adds[i].type,
					       state->adds[i].ttl,
					       state->adds[i].data);
			}
		}
	} else {
		if (state->log != NULL)
			state->log(ISC_LOG_INFO, "STR"
				   "STR", zone);
	}
	memset(state->adds, 0, sizeof(state->adds));
	memset(state->deletes, 0, sizeof(state->deletes));
}