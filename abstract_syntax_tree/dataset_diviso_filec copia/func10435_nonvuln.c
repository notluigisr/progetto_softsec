static void __d_move(struct dentry *dentry, struct dentry *target,
		     bool exchange)
{
	struct inode *dir = NULL;
	unsigned n;
	if (!dentry->d_inode)
		printk(KERN_WARNING "STR");

	BUG_ON(d_ancestor(dentry, target));
	BUG_ON(d_ancestor(target, dentry));

	dentry_lock_for_move(dentry, target);
	if (unlikely(d_in_lookup(target))) {
		dir = target->d_parent->d_inode;
		n = start_dir_add(dir);
		__d_lookup_done(target);
	}

	write_seqcount_begin(&dentry->d_seq);
	write_seqcount_begin_nested(&target->d_seq, DENTRY_D_LOCK_NESTED);

	
	
	__d_drop(dentry);
	__d_drop(target);

	
	if (exchange)
		swap_names(dentry, target);
	else
		copy_name(dentry, target);

	
	__d_rehash(dentry);
	if (exchange)
		__d_rehash(target);

	
	if (IS_ROOT(dentry)) {
		
		dentry->d_flags |= DCACHE_RCUACCESS;
		dentry->d_parent = target->d_parent;
		target->d_parent = target;
		list_del_init(&target->d_child);
		list_move(&dentry->d_child, &dentry->d_parent->d_subdirs);
	} else {
		
		swap(dentry->d_parent, target->d_parent);
		list_move(&target->d_child, &target->d_parent->d_subdirs);
		list_move(&dentry->d_child, &dentry->d_parent->d_subdirs);
		if (exchange)
			fsnotify_update_flags(target);
		fsnotify_update_flags(dentry);
	}

	write_seqcount_end(&target->d_seq);
	write_seqcount_end(&dentry->d_seq);

	if (dir)
		end_dir_add(dir, n);
	dentry_unlock_for_move(dentry, target);
}