int nfs_symlink(struct user_namespace *mnt_userns, struct inode *dir,
		struct dentry *dentry, const char *symname)
{
	struct page *page;
	char *kaddr;
	struct iattr attr;
	unsigned int pathlen = strlen(symname);
	int error;

	dfprintk(VFS, "STR", dir->i_sb->s_id,
		dir->i_ino, dentry, symname);

	if (pathlen > PAGE_SIZE)
		return -ENAMETOOLONG;

	attr.ia_mode = S_IFLNK | S_IRWXUGO;
	attr.ia_valid = ATTR_MODE;

	page = alloc_page(GFP_USER);
	if (!page)
		return -ENOMEM;

	kaddr = page_address(page);
	memcpy(kaddr, symname, pathlen);
	if (pathlen < PAGE_SIZE)
		memset(kaddr + pathlen, 0, PAGE_SIZE - pathlen);

	trace_nfs_symlink_enter(dir, dentry);
	error = NFS_PROTO(dir)->symlink(dir, dentry, page, pathlen, &attr);
	trace_nfs_symlink_exit(dir, dentry, error);
	if (error != 0) {
		dfprintk(VFS, "STR",
			dir->i_sb->s_id, dir->i_ino,
			dentry, symname, error);
		d_drop(dentry);
		__free_page(page);
		return error;
	}

	nfs_set_verifier(dentry, nfs_save_change_attribute(dir));

	
	if (!add_to_page_cache_lru(page, d_inode(dentry)->i_mapping, 0,
							GFP_KERNEL)) {
		SetPageUptodate(page);
		unlock_page(page);
		
		put_page(page);
	} else
		__free_page(page);

	return 0;
}