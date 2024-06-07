static int inotify_add_to_idr(struct idr *idr, spinlock_t *idr_lock,
			      int *last_wd,
			      struct inotify_inode_mark *i_mark)
{
	int ret;

	do {
		if (unlikely(!idr_pre_get(idr, GFP_KERNEL)))
			return -ENOMEM;

		spin_lock(idr_lock);
		ret = idr_get_new_above(idr, i_mark, *last_wd + 1,
					&i_mark->wd);
		
		if (!ret) {
			*last_wd = i_mark->wd;
			fsnotify_get_mark(&i_mark->fsn_mark);
		}
		spin_unlock(idr_lock);
	} while (ret == -EAGAIN);

	return ret;
}