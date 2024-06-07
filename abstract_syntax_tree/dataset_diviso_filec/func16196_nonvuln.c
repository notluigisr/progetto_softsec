static int selinux_sb_kern_mount(struct super_block *sb, int flags, void *data)
{
	const struct cred *cred = current_cred();
	struct common_audit_data ad;
	struct selinux_audit_data sad = {0,};
	int rc;

	rc = superblock_doinit(sb, data);
	if (rc)
		return rc;

	
	if (flags & MS_KERNMOUNT)
		return 0;

	COMMON_AUDIT_DATA_INIT(&ad, DENTRY);
	ad.selinux_audit_data = &sad;
	ad.u.dentry = sb->s_root;
	return superblock_has_perm(cred, sb, FILESYSTEM__MOUNT, &ad);
}