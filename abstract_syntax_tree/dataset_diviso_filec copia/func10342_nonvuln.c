static struct cgroup_mount_point *lxc_cgroup_find_mount_point(struct cgroup_hierarchy *hierarchy, const char *group, bool should_be_writable)
{
	struct cgroup_mount_point **mps;
	struct cgroup_mount_point *current_result = NULL;
	ssize_t quality = -1;

	
	if (hierarchy->rw_absolute_mount_point)
		return hierarchy->rw_absolute_mount_point;
	if (!should_be_writable && hierarchy->ro_absolute_mount_point)
		return hierarchy->ro_absolute_mount_point;

	for (mps = hierarchy->all_mount_points; mps && *mps; mps++) {
		struct cgroup_mount_point *mp = *mps;
		size_t prefix_len = mp->mount_prefix ? strlen(mp->mount_prefix) : 0;

		if (prefix_len == 1 && mp->mount_prefix[0] == '/')
			prefix_len = 0;

		if (should_be_writable && mp->read_only)
			continue;

		if (!prefix_len ||
		    (strncmp(group, mp->mount_prefix, prefix_len) == 0 &&
		     (group[prefix_len] == '\0' || group[prefix_len] == '/'))) {
			
			if (quality == -1 || prefix_len < quality) {
				current_result = mp;
				quality = prefix_len;
			}
		}
	}

	if (!current_result)
		errno = ENOENT;
	return current_result;
}