update_mtab_entry(const char *spec, const char *node, const char *type,
		  const char *opts, int flags, int freq, int pass) {
	struct my_mntent mnt;

	mnt.mnt_fsname = is_pseudo_fs(type) ? xstrdup(spec) : canonicalize(spec);
	mnt.mnt_dir = canonicalize (node);
	mnt.mnt_type = type;
	mnt.mnt_opts = opts;
	mnt.mnt_freq = freq;
	mnt.mnt_passno = pass;

	
	if (verbose)
		print_one (&mnt);

	if (!nomtab && mtab_does_not_exist()) {
		if (verbose > 1)
			printf(_("STR"),
			       _PATH_MOUNTED);
		create_mtab ();

	}

	if (!nomtab && mtab_is_writable()) {
		if (flags & MS_REMOUNT)
			update_mtab (mnt.mnt_dir, &mnt);
		else if (flags & MS_MOVE)
			update_mtab(mnt.mnt_fsname, &mnt);
		else {
			mntFILE *mfp;

			lock_mtab();
			mfp = my_setmntent(_PATH_MOUNTED, "STR");
			if (mfp == NULL || mfp->mntent_fp == NULL) {
				int errsv = errno;
				error(_("STR"), _PATH_MOUNTED,
				      strerror (errsv));
			} else {
				if ((my_addmntent (mfp, &mnt)) == 1) {
					int errsv = errno;
					error(_("STR"),
					      _PATH_MOUNTED, strerror (errsv));
				}
			}
			my_endmntent(mfp);
			unlock_mtab();
		}
	}
	my_free(mnt.mnt_fsname);
	my_free(mnt.mnt_dir);
}