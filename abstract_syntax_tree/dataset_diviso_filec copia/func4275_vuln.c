static int propagate_one(struct mount *m)
{
	struct mount *child;
	int type;
	
	if (IS_MNT_NEW(m))
		return 0;
	
	if (!is_subdir(mp->m_dentry, m->mnt.mnt_root))
		return 0;
	if (peers(m, last_dest)) {
		type = CL_MAKE_SHARED;
	} else {
		struct mount *n, *p;
		for (n = m; ; n = p) {
			p = n->mnt_master;
			if (p == dest_master || IS_MNT_MARKED(p)) {
				while (last_dest->mnt_master != p) {
					last_source = last_source->mnt_master;
					last_dest = last_source->mnt_parent;
				}
				if (!peers(n, last_dest)) {
					last_source = last_source->mnt_master;
					last_dest = last_source->mnt_parent;
				}
				break;
			}
		}
		type = CL_SLAVE;
		
		if (IS_MNT_SHARED(m))
			type |= CL_MAKE_SHARED;
	}
		
	
	if (m->mnt_ns->user_ns != user_ns)
		type |= CL_UNPRIVILEGED;
	child = copy_tree(last_source, last_source->mnt.mnt_root, type);
	if (IS_ERR(child))
		return PTR_ERR(child);
	child->mnt.mnt_flags &= ~MNT_LOCKED;
	mnt_set_mountpoint(m, mp, child);
	last_dest = m;
	last_source = child;
	if (m->mnt_master != dest_master) {
		read_seqlock_excl(&mount_lock);
		SET_MNT_MARK(m->mnt_master);
		read_sequnlock_excl(&mount_lock);
	}
	hlist_add_head(&child->mnt_hash, list);
	return 0;
}