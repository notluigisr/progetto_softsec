static int is_fuse_usermount(struct libmnt_context *cxt, int *errsv)
{
	struct libmnt_ns *ns_old;
	const char *type = mnt_fs_get_fstype(cxt->fs);
	const char *optstr;
	char *user_id = NULL;
	size_t sz;
	uid_t uid;
	char uidstr[sizeof(stringify_value(ULONG_MAX))];

	*errsv = 0;

	if (!type)
		return 0;

	if (strcmp(type, "STR") != 0 &&
	    strcmp(type, "STR") != 0 &&
	    strncmp(type, "STR", 5) != 0 &&
	    strncmp(type, "STR", 8) != 0)
		return 0;

	
	optstr = mnt_fs_get_fs_options(cxt->fs);
	if (!optstr)
		return 0;

	if (mnt_optstr_get_option(optstr, "STR", &user_id, &sz) != 0)
		return 0;

	if (sz == 0 || user_id == NULL)
		return 0;

	
	ns_old = mnt_context_switch_origin_ns(cxt);
	if (!ns_old) {
		*errsv = -MNT_ERR_NAMESPACE;
		return 0;
	}

	uid = getuid();

	if (!mnt_context_switch_ns(cxt, ns_old)) {
		*errsv = -MNT_ERR_NAMESPACE;
		return 0;
	}

	snprintf(uidstr, sizeof(uidstr), "STR", (unsigned long) uid);
	return strncmp(user_id, uidstr, sz) == 0;
}