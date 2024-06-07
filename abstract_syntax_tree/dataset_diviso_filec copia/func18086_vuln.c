static int inotify_update_existing_watch(struct fsnotify_group *group,
					 struct inode *inode,
					 u32 arg)
{
	struct fsnotify_mark *fsn_mark;
	struct inotify_inode_mark *i_mark;
	__u32 old_mask, new_mask;
	__u32 mask;
	int add = (arg & IN_MASK_ADD);
	int create = (arg & IN_MASK_CREATE);
	int ret;

	mask = inotify_arg_to_mask(arg);

	fsn_mark = fsnotify_find_mark(&inode->i_fsnotify_marks, group);
	if (!fsn_mark)
		return -ENOENT;
	else if (create)
		return -EEXIST;

	i_mark = container_of(fsn_mark, struct inotify_inode_mark, fsn_mark);

	spin_lock(&fsn_mark->lock);
	old_mask = fsn_mark->mask;
	if (add)
		fsn_mark->mask |= mask;
	else
		fsn_mark->mask = mask;
	new_mask = fsn_mark->mask;
	spin_unlock(&fsn_mark->lock);

	if (old_mask != new_mask) {
		
		int dropped = (old_mask & ~new_mask);
		
		int do_inode = (new_mask & ~inode->i_fsnotify_mask);

		
		if (dropped || do_inode)
			fsnotify_recalc_mask(inode->i_fsnotify_marks);

	}

	
	ret = i_mark->wd;

	
	fsnotify_put_mark(fsn_mark);

	return ret;
}