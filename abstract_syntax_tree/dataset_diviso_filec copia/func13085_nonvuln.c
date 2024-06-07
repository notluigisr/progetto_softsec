zfs_znode_acl_version(znode_t *zp)
{
	zfs_acl_phys_t acl_phys;

	if (zp->z_is_sa)
		return (ZFS_ACL_VERSION_FUID);
	else {
		int error;

		
		if ((error = sa_lookup(zp->z_sa_hdl,
		    SA_ZPL_ZNODE_ACL(zp->z_zfsvfs),
		    &acl_phys, sizeof (acl_phys))) == 0)
			return (acl_phys.z_acl_version);
		else {
			
			VERIFY(zp->z_is_sa && error == ENOENT);
			return (ZFS_ACL_VERSION_FUID);
		}
	}
}