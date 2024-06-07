compat_do_replace(struct net *net, sockptr_t arg, unsigned int len)
{
	int ret;
	struct compat_ip6t_replace tmp;
	struct xt_table_info *newinfo;
	void *loc_cpu_entry;
	struct ip6t_entry *iter;

	if (copy_from_sockptr(&tmp, arg, sizeof(tmp)) != 0)
		return -EFAULT;

	
	if (tmp.num_counters >= INT_MAX / sizeof(struct xt_counters))
		return -ENOMEM;
	if (tmp.num_counters == 0)
		return -EINVAL;

	tmp.name[sizeof(tmp.name)-1] = 0;

	newinfo = xt_alloc_table_info(tmp.size);
	if (!newinfo)
		return -ENOMEM;

	loc_cpu_entry = newinfo->entries;
	if (copy_from_sockptr_offset(loc_cpu_entry, arg, sizeof(tmp),
			tmp.size) != 0) {
		ret = -EFAULT;
		goto free_newinfo;
	}

	ret = translate_compat_table(net, &newinfo, &loc_cpu_entry, &tmp);
	if (ret != 0)
		goto free_newinfo;

	ret = __do_replace(net, tmp.name, tmp.valid_hooks, newinfo,
			   tmp.num_counters, compat_ptr(tmp.counters));
	if (ret)
		goto free_newinfo_untrans;
	return 0;

 free_newinfo_untrans:
	xt_entry_foreach(iter, loc_cpu_entry, newinfo->size)
		cleanup_entry(iter, net);
 free_newinfo:
	xt_free_table_info(newinfo);
	return ret;
}