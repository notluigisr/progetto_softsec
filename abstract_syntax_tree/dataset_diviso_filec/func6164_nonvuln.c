int nfs_instantiate(struct dentry *dentry, struct nfs_fh *fhandle,
				struct nfs_fattr *fattr)
{
	struct inode *inode;
	int error = -EACCES;

	
	if (dentry->d_inode)
		return 0;
	if (fhandle->size == 0) {
		struct inode *dir = dentry->d_parent->d_inode;
		error = NFS_PROTO(dir)->lookup(dir, &dentry->d_name, fhandle, fattr);
		if (error)
			return error;
	}
	if (!(fattr->valid & NFS_ATTR_FATTR)) {
		struct nfs_server *server = NFS_SB(dentry->d_sb);
		error = server->nfs_client->rpc_ops->getattr(server, fhandle, fattr);
		if (error < 0)
			return error;
	}
	inode = nfs_fhget(dentry->d_sb, fhandle, fattr);
	error = PTR_ERR(inode);
	if (IS_ERR(inode))
		return error;
	d_instantiate(dentry, inode);
	if (d_unhashed(dentry))
		d_rehash(dentry);
	return 0;
}