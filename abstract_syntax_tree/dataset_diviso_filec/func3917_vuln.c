static struct dentry *nfs_readdir_lookup(nfs_readdir_descriptor_t *desc)
{
	struct dentry *parent = desc->file->f_path.dentry;
	struct inode *dir = parent->d_inode;
	struct nfs_entry *entry = desc->entry;
	struct dentry *dentry, *alias;
	struct qstr name = {
		.name = entry->name,
		.len = entry->len,
	};
	struct inode *inode;

	switch (name.len) {
		case 2:
			if (name.name[0] == '.' && name.name[1] == '.')
				return dget_parent(parent);
			break;
		case 1:
			if (name.name[0] == '.')
				return dget(parent);
	}
	name.hash = full_name_hash(name.name, name.len);
	dentry = d_lookup(parent, &name);
	if (dentry != NULL) {
		
		if (dentry->d_inode != NULL &&
				(NFS_FILEID(dentry->d_inode) == entry->ino ||
				d_mountpoint(dentry))) {
			if (!desc->plus || entry->fh->size == 0)
				return dentry;
			if (nfs_compare_fh(NFS_FH(dentry->d_inode),
						entry->fh) == 0)
				goto out_renew;
		}
		
		d_drop(dentry);
		dput(dentry);
	}
	if (!desc->plus || !(entry->fattr->valid & NFS_ATTR_FATTR))
		return NULL;
	
	dentry = d_alloc(parent, &name);
	if (dentry == NULL)
		return NULL;
	dentry->d_op = NFS_PROTO(dir)->dentry_ops;
	inode = nfs_fhget(dentry->d_sb, entry->fh, entry->fattr);
	if (IS_ERR(inode)) {
		dput(dentry);
		return NULL;
	}

	alias = d_materialise_unique(dentry, inode);
	if (alias != NULL) {
		dput(dentry);
		if (IS_ERR(alias))
			return NULL;
		dentry = alias;
	}

	nfs_renew_times(dentry);
	nfs_set_verifier(dentry, nfs_save_change_attribute(dir));
	return dentry;
out_renew:
	nfs_renew_times(dentry);
	nfs_refresh_verifier(dentry, nfs_save_change_attribute(dir));
	return dentry;
}