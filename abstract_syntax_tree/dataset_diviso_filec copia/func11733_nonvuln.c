int audit_add_tree_rule(struct audit_krule *rule)
{
	struct audit_tree *seed = rule->tree, *tree;
	struct path path;
	struct vfsmount *mnt, *p;
	struct list_head list;
	int err;

	list_for_each_entry(tree, &tree_list, list) {
		if (!strcmp(seed->pathname, tree->pathname)) {
			put_tree(seed);
			rule->tree = tree;
			list_add(&rule->rlist, &tree->rules);
			return 0;
		}
	}
	tree = seed;
	list_add(&tree->list, &tree_list);
	list_add(&rule->rlist, &tree->rules);
	
	mutex_unlock(&audit_filter_mutex);

	err = kern_path(tree->pathname, 0, &path);
	if (err)
		goto Err;
	mnt = collect_mounts(path.mnt, path.dentry);
	path_put(&path);
	if (!mnt) {
		err = -ENOMEM;
		goto Err;
	}
	list_add_tail(&list, &mnt->mnt_list);

	get_tree(tree);
	list_for_each_entry(p, &list, mnt_list) {
		err = tag_chunk(p->mnt_root->d_inode, tree);
		if (err)
			break;
	}

	list_del(&list);
	drop_collected_mounts(mnt);

	if (!err) {
		struct node *node;
		spin_lock(&hash_lock);
		list_for_each_entry(node, &tree->chunks, list)
			node->index &= ~(1U<<31);
		spin_unlock(&hash_lock);
	} else {
		trim_marked(tree);
		goto Err;
	}

	mutex_lock(&audit_filter_mutex);
	if (list_empty(&rule->rlist)) {
		put_tree(tree);
		return -ENOENT;
	}
	rule->tree = tree;
	put_tree(tree);

	return 0;
Err:
	mutex_lock(&audit_filter_mutex);
	list_del_init(&tree->list);
	list_del_init(&tree->rules);
	put_tree(tree);
	return err;
}