static void ikev2_parent_inI1outR1_continue(struct pluto_crypto_req_cont *pcrc,
					    struct pluto_crypto_req *r,
					    err_t ugh)
{
	struct ke_continuation *ke = (struct ke_continuation *)pcrc;
	struct msg_digest *md = ke->md;
	struct state *const st = md->st;
	stf_status e;

	DBG(DBG_CONTROLMORE,
	    DBG_log("STR"));

	if (st == NULL) {
		loglog(RC_LOG_SERIOUS,
		       "STR",
		       __FUNCTION__);
		if (ke->md)
			release_md(ke->md);
		return;
	}

	
	passert(ugh == NULL);
	passert(cur_state == NULL);
	passert(st != NULL);

	passert(st->st_suspended_md == ke->md);
	set_suspended(st, NULL); 

	set_cur_state(st);

	st->st_calculating = FALSE;

	e = ikev2_parent_inI1outR1_tail(pcrc, r);

	if (ke->md != NULL) {
		complete_v2_state_transition(&ke->md, e);
		if (ke->md)
			release_md(ke->md);
	}
	reset_globals();

	passert(GLOBALS_ARE_RESET());
}