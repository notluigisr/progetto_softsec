zfs_acl_alloc(int vers)
{
	zfs_acl_t *aclp;

	aclp = kmem_zalloc(sizeof (zfs_acl_t), KM_SLEEP);
	list_create(&aclp->z_acl, sizeof (zfs_acl_node_t),
	    offsetof(zfs_acl_node_t, z_next));
	aclp->z_version = vers;
	if (vers == ZFS_ACL_VERSION_FUID)
		aclp->z_ops = &zfs_acl_fuid_ops;
	else
		aclp->z_ops = &zfs_acl_v0_ops;
	return (aclp);
}