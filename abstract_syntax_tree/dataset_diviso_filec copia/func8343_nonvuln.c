static void shmem_destroy_inode(struct inode *inode)
{
	if ((inode->i_mode & S_IFMT) == S_IFREG) {
		
		mpol_free_shared_policy(&SHMEM_I(inode)->policy);
	}
	shmem_acl_destroy_inode(inode);
	kmem_cache_free(shmem_inode_cachep, SHMEM_I(inode));
}