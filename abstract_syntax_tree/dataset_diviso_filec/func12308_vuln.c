stf_status ikev2parent_inI2outR2(struct msg_digest *md)
{
	struct state *st = md->st;

	

	

	DBG(DBG_CONTROLMORE,
	    DBG_log(
		    "STR"));

	
	if (!md->chain[ISAKMP_NEXT_v2E]) {
		libreswan_log("STR");
		reset_globals();
		return STF_FATAL;
	}

	
	{
		struct dh_continuation *dh = alloc_thing(
			struct dh_continuation,
			"STR");
		stf_status e;

		dh->md = md;
		set_suspended(st, dh->md);

		pcrc_init(&dh->dh_pcrc);
		dh->dh_pcrc.pcrc_func = ikev2_parent_inI2outR2_continue;
		e = start_dh_v2(&dh->dh_pcrc, st, st->st_import, RESPONDER,
				st->st_oakley.groupnum);
		if (e != STF_SUSPEND && e != STF_INLINE) {
			loglog(RC_CRYPTOFAILED, "STR");
			delete_state(st);
		}

		reset_globals();

		return e;
	}
}