int audit_tag_tree(char *old, char *new)
{
	struct list_head cursor, barrier;
	int failed = 0;
	struct path path;
	struct vfsmount *tagged;
	struct list_head list;
	struct vfsmount *mnt;
	struct dentry *dentry;
	int err;

	err = kern_path(new, 0, &path);
	if (err)
		return err;
	tagged = collect_mounts(path.mnt, path.dentry);
	path_put(&path);
	if (!tagged)
		return -ENOMEM;

	err = kern_path(old, 0, &path);
	if (err) {
		drop_collected_mounts(tagged);
		return err;
	}
	mnt = mntget(path.mnt);
	dentry = dget(path.dentry);
	path_put(&path);

	if (dentry == tagged->mnt_root && dentry == mnt->mnt_root)
		follow_up(&mnt, &dentry);

	list_add_tail(&list, &tagged->mnt_list);

	mutex_lock(&audit_filter_mutex);
	list_add(&barrier, &tree_list);
	list_add(&cursor, &barrier);

	while (cursor.next != &tree_list) {
		struct audit_tree *tree;
		struct vfsmount *p;

		tree = container_of(cursor.next, struct audit_tree, list);
		get_tree(tree);
		list_del(&cursor);
		list_add(&cursor, &tree->list);
		mutex_unlock(&audit_filter_mutex);

		err = kern_path(tree->pathname, 0, &path);
		if (err) {
			put_tree(tree);
			mutex_lock(&audit_filter_mutex);
			continue;
		}

		spin_lock(&vfsmount_lock);
		if (!is_under(mnt, dentry, &path)) {
			spin_unlock(&vfsmount_lock);
			path_put(&path);
			put_tree(tree);
			mutex_lock(&audit_filter_mutex);
			continue;
		}
		spin_unlock(&vfsmount_lock);
		path_put(&path);

		list_for_each_entry(p, &list, mnt_list) {
			failed = tag_chunk(p->mnt_root->d_inode, tree);
			if (failed)
				break;
		}

		if (failed) {
			put_tree(tree);
			mutex_lock(&audit_filter_mutex);
			break;
		}

		mutex_lock(&audit_filter_mutex);
		spin_lock(&hash_lock);
		if (!tree->goner) {
			list_del(&tree->list);
			list_add(&tree->list, &tree_list);
		}
		spin_unlock(&hash_lock);
		put_tree(tree);
	}

	while (barrier.prev != &tree_list) {
		struct audit_tree *tree;

		tree = container_of(barrier.prev, struct audit_tree, list);
		get_tree(tree);
		list_del(&tree->list);
		list_add(&tree->list, &barrier);
		mutex_unlock(&audit_filter_mutex);

		if (!failed) {
			struct node *node;
			spin_lock(&hash_lock);
			list_for_each_entry(node, &tree->chunks, list)
				node->index &= ~(1U<<31);
			spin_unlock(&hash_lock);
		} else {
			trim_marked(tree);
		}

		put_tree(tree);
		mutex_lock(&audit_filter_mutex);
	}
	list_del(&barrier);
	list_del(&cursor);
	list_del(&list);
	mutex_unlock(&audit_filter_mutex);
	dput(dentry);
	mntput(mnt);
	drop_collected_mounts(tagged);
	return failed;
}