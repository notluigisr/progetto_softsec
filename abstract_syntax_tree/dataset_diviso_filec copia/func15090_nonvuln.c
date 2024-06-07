getmntdevbackward (const char *name, struct mntentchn *mcprev) {
	struct mntentchn *mc, *mc0;

	mc0 = mtab_head();
	if (!mcprev)
		mcprev = mc0;

	
	for (mc = mcprev->prev; mc && mc != mc0; mc = mc->prev) {
		if (streq(mc->m.mnt_fsname, name))
			return mc;
	}

	
	for (mc = mcprev->prev; mc && mc != mc0; mc = mc->prev) {
		char *cn = canonicalize(mc->m.mnt_fsname);
		int res = cn ? streq(cn, name) : 0;

		free(cn);
		if (res)
			return mc;
	}

	return NULL;
}