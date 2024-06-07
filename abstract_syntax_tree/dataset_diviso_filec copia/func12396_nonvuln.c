static void v9fs_i_callback(struct rcu_head *head)
{
	struct inode *inode = container_of(head, struct inode, i_rcu);
	kmem_cache_free(v9fs_inode_cache, V9FS_I(inode));
}