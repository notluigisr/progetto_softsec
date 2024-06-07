static int v9fs_vfs_setattr(struct dentry *dentry, struct iattr *iattr)
{
	int retval;
	struct v9fs_session_info *v9ses;
	struct p9_fid *fid;
	struct p9_wstat wstat;

	p9_debug(P9_DEBUG_VFS, "STR");
	retval = setattr_prepare(dentry, iattr);
	if (retval)
		return retval;

	retval = -EPERM;
	v9ses = v9fs_dentry2v9ses(dentry);
	fid = v9fs_fid_lookup(dentry);
	if(IS_ERR(fid))
		return PTR_ERR(fid);

	v9fs_blank_wstat(&wstat);
	if (iattr->ia_valid & ATTR_MODE)
		wstat.mode = unixmode2p9mode(v9ses, iattr->ia_mode);

	if (iattr->ia_valid & ATTR_MTIME)
		wstat.mtime = iattr->ia_mtime.tv_sec;

	if (iattr->ia_valid & ATTR_ATIME)
		wstat.atime = iattr->ia_atime.tv_sec;

	if (iattr->ia_valid & ATTR_SIZE)
		wstat.length = iattr->ia_size;

	if (v9fs_proto_dotu(v9ses)) {
		if (iattr->ia_valid & ATTR_UID)
			wstat.n_uid = iattr->ia_uid;

		if (iattr->ia_valid & ATTR_GID)
			wstat.n_gid = iattr->ia_gid;
	}

	
	if (d_is_reg(dentry))
		filemap_write_and_wait(d_inode(dentry)->i_mapping);

	retval = p9_client_wstat(fid, &wstat);
	if (retval < 0)
		return retval;

	if ((iattr->ia_valid & ATTR_SIZE) &&
	    iattr->ia_size != i_size_read(d_inode(dentry)))
		truncate_setsize(d_inode(dentry), iattr->ia_size);

	v9fs_invalidate_inode_attr(d_inode(dentry));

	setattr_copy(d_inode(dentry), iattr);
	mark_inode_dirty(d_inode(dentry));
	return 0;
}