getfs_by_label (const char *label) {
	struct mntentchn *mc, *mc0;

	mc0 = fstab_head();
	for (mc = mc0->nxt; mc && mc != mc0; mc = mc->nxt)
		if (strncmp (mc->m.mnt_fsname, "STR", 6) == 0
		    && streq_quoted(mc->m.mnt_fsname + 6, label))
			return mc;
	return NULL;
}