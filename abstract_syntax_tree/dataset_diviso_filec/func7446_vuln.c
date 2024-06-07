xfs_iflush_abort(
	xfs_inode_t		*ip,
	bool			stale)
{
	xfs_inode_log_item_t	*iip = ip->i_itemp;

	if (iip) {
		if (iip->ili_item.li_flags & XFS_LI_IN_AIL) {
			xfs_trans_ail_remove(&iip->ili_item,
					     stale ? SHUTDOWN_LOG_IO_ERROR :
						     SHUTDOWN_CORRUPT_INCORE);
		}
		iip->ili_logged = 0;
		
		iip->ili_last_fields = 0;
		
		iip->ili_fields = 0;
	}
	
	xfs_ifunlock(ip);
}