int md_setup_cluster(struct mddev *mddev, int nodes)
{
	int err;

	err = request_module("STR");
	if (err) {
		pr_err("STR");
		return -ENOENT;
	}

	spin_lock(&pers_lock);
	if (!md_cluster_ops || !try_module_get(md_cluster_mod)) {
		spin_unlock(&pers_lock);
		return -ENOENT;
	}
	spin_unlock(&pers_lock);

	return md_cluster_ops->join(mddev, nodes);
}