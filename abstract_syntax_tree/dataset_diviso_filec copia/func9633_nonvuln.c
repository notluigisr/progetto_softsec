xfs_inode_item_destroy(
	xfs_inode_t	*ip)
{
	kmem_zone_free(xfs_ili_zone, ip->i_itemp);
}