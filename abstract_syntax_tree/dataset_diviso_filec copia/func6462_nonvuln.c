dump_calc_estimates(
    disk_estimates_t *	est)
{
    int level;
    off_t size;
    char *errmsg=NULL, *qerrmsg;

    for(level = 0; level < DUMP_LEVELS; level++) {
	if(est->est[level].needestimate) {
	    dbprintf(_("STR"),
		      est->qamname, level);
	    size = getsize_dump(est->dle, level, &errmsg);

	    amflock(1, "STR");

	    g_printf(_("STR"),
		   est->qamname, level, (long long)size);
	    if (errmsg && errmsg[0] != '\0') {
		if(am_has_feature(g_options->features,
				  fe_rep_sendsize_quoted_error)) {
		    qerrmsg = quote_string(errmsg);
		    dbprintf(_("STR"), errmsg);
		    g_printf("STR",
			   est->qamname, level, qerrmsg);
		    amfree(qerrmsg);
		}
	    }
	    amfree(errmsg);
	    fflush(stdout);

	    amfunlock(1, "STR");
	}
    }
}