static bool cgroup_check_hierarchy_limits(struct cgroup *parent)
{
	struct cgroup *cgroup;
	int ret = false;
	int level = 1;

	lockdep_assert_held(&cgroup_mutex);

	for (cgroup = parent; cgroup; cgroup = cgroup_parent(cgroup)) {
		if (cgroup->nr_descendants >= cgroup->max_descendants)
			goto fail;

		if (level > cgroup->max_depth)
			goto fail;

		level++;
	}

	ret = true;
fail:
	return ret;
}