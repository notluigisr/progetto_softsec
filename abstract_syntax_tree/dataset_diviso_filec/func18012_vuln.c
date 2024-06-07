int ecryptfs_write_metadata(struct dentry *ecryptfs_dentry)
{
	struct ecryptfs_crypt_stat *crypt_stat =
		&ecryptfs_inode_to_private(ecryptfs_dentry->d_inode)->crypt_stat;
	char *virt;
	size_t size = 0;
	int rc = 0;

	if (likely(crypt_stat->flags & ECRYPTFS_ENCRYPTED)) {
		if (!(crypt_stat->flags & ECRYPTFS_KEY_VALID)) {
			printk(KERN_ERR "STR");
			rc = -EINVAL;
			goto out;
		}
	} else {
		printk(KERN_WARNING "STR",
		       __func__);
		rc = -EINVAL;
		goto out;
	}
	
	virt = (char *)get_zeroed_page(GFP_KERNEL);
	if (!virt) {
		printk(KERN_ERR "STR", __func__);
		rc = -ENOMEM;
		goto out;
	}
	rc = ecryptfs_write_headers_virt(virt, PAGE_CACHE_SIZE, &size,
					 crypt_stat, ecryptfs_dentry);
	if (unlikely(rc)) {
		printk(KERN_ERR "STR",
		       __func__, rc);
		goto out_free;
	}
	if (crypt_stat->flags & ECRYPTFS_METADATA_IN_XATTR)
		rc = ecryptfs_write_metadata_to_xattr(ecryptfs_dentry,
						      crypt_stat, virt, size);
	else
		rc = ecryptfs_write_metadata_to_contents(crypt_stat,
							 ecryptfs_dentry, virt);
	if (rc) {
		printk(KERN_ERR "STR"
		       "STR", __func__, rc);
		goto out_free;
	}
out_free:
	free_page((unsigned long)virt);
out:
	return rc;
}