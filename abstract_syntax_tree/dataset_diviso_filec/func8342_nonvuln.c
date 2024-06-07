static int tomoyo_path_symlink(struct path *parent, struct dentry *dentry,
			       const char *old_name)
{
	struct path path = { parent->mnt, dentry };
	return tomoyo_check_1path_perm(tomoyo_domain(),
				       TOMOYO_TYPE_SYMLINK_ACL,
				       &path);
}