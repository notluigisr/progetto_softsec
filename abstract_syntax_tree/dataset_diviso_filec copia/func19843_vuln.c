int orangefs_set_acl(struct inode *inode, struct posix_acl *acl, int type)
{
	struct orangefs_inode_s *orangefs_inode = ORANGEFS_I(inode);
	int error = 0;
	void *value = NULL;
	size_t size = 0;
	const char *name = NULL;

	switch (type) {
	case ACL_TYPE_ACCESS:
		name = XATTR_NAME_POSIX_ACL_ACCESS;
		if (acl) {
			umode_t mode = inode->i_mode;
			
			error = posix_acl_equiv_mode(acl, &mode);
			if (error < 0) {
				gossip_err("STR",
					   __func__,
					   error);
				return error;
			}

			if (inode->i_mode != mode)
				SetModeFlag(orangefs_inode);
			inode->i_mode = mode;
			mark_inode_dirty_sync(inode);
			if (error == 0)
				acl = NULL;
		}
		break;
	case ACL_TYPE_DEFAULT:
		name = XATTR_NAME_POSIX_ACL_DEFAULT;
		break;
	default:
		gossip_err("STR", __func__, type);
		return -EINVAL;
	}

	gossip_debug(GOSSIP_ACL_DEBUG,
		     "STR",
		     __func__, get_khandle_from_ino(inode),
		     name,
		     type);

	if (acl) {
		size = posix_acl_xattr_size(acl->a_count);
		value = kmalloc(size, GFP_KERNEL);
		if (!value)
			return -ENOMEM;

		error = posix_acl_to_xattr(&init_user_ns, acl, value, size);
		if (error < 0)
			goto out;
	}

	gossip_debug(GOSSIP_ACL_DEBUG,
		     "STR",
		     __func__, name, value, size, acl);
	
	error = orangefs_inode_setxattr(inode, name, value, size, 0);

out:
	kfree(value);
	if (!error)
		set_cached_acl(inode, type, acl);
	return error;
}