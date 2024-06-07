static int selinux_inode_removexattr(struct user_namespace *mnt_userns,
				     struct dentry *dentry, const char *name)
{
	if (strcmp(name, XATTR_NAME_SELINUX)) {
		int rc = cap_inode_removexattr(mnt_userns, dentry, name);
		if (rc)
			return rc;

		
		return dentry_has_perm(current_cred(), dentry, FILE__SETATTR);
	}

	if (!selinux_initialized(&selinux_state))
		return 0;

	
	return -EACCES;
}