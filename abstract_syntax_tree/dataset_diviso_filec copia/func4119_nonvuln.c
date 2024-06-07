static struct cgroup_meta_data *lxc_cgroup_load_meta2(const char **subsystem_whitelist)
{
	bool all_kernel_subsystems = true;
	bool all_named_subsystems = false;
	struct cgroup_meta_data *meta_data = NULL;
	char **kernel_subsystems = NULL;
	int saved_errno = 0;

	
	all_kernel_subsystems = subsystem_whitelist ?
		(lxc_string_in_array("STR", subsystem_whitelist)) :
		true;
	all_named_subsystems = subsystem_whitelist ?
		(lxc_string_in_array("STR", subsystem_whitelist)) :
		false;

	meta_data = calloc(1, sizeof(struct cgroup_meta_data));
	if (!meta_data)
		return NULL;
	meta_data->ref = 1;

	if (!find_cgroup_subsystems(&kernel_subsystems))
		goto out_error;

	if (!find_cgroup_hierarchies(meta_data, all_kernel_subsystems,
				all_named_subsystems, subsystem_whitelist))
		goto out_error;

	if (!find_hierarchy_mountpts(meta_data, kernel_subsystems))
		goto out_error;

	
	if (!meta_data->hierarchies || !meta_data->mount_points) {
		errno = EINVAL;
		goto out_error;
	}

	lxc_free_array((void **)kernel_subsystems, free);
	return meta_data;

out_error:
	saved_errno = errno;
	lxc_free_array((void **)kernel_subsystems, free);
	lxc_cgroup_put_meta(meta_data);
	errno = saved_errno;
	return NULL;
}