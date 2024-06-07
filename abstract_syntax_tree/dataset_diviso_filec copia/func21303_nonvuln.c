static int selinux_inode_init_security(struct inode *inode, struct inode *dir,
				       const struct qstr *qstr,
				       const char **name,
				       void **value, size_t *len)
{
	const struct task_security_struct *tsec = current_security();
	struct superblock_security_struct *sbsec;
	u32 sid, newsid, clen;
	int rc;
	char *context;

	sbsec = dir->i_sb->s_security;

	sid = tsec->sid;
	newsid = tsec->create_sid;

	rc = selinux_determine_inode_label(current_security(),
		dir, qstr,
		inode_mode_to_security_class(inode->i_mode),
		&newsid);
	if (rc)
		return rc;

	
	if (sbsec->flags & SE_SBINITIALIZED) {
		struct inode_security_struct *isec = inode->i_security;
		isec->sclass = inode_mode_to_security_class(inode->i_mode);
		isec->sid = newsid;
		isec->initialized = LABEL_INITIALIZED;
	}

	if (!ss_initialized || !(sbsec->flags & SBLABEL_MNT))
		return -EOPNOTSUPP;

	if (name)
		*name = XATTR_SELINUX_SUFFIX;

	if (value && len) {
		rc = security_sid_to_context_force(newsid, &context, &clen);
		if (rc)
			return rc;
		*value = context;
		*len = clen;
	}

	return 0;
}