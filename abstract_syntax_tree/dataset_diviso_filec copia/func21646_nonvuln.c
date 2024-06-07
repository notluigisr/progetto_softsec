static void *mdesc_iterate_over_cpus(void *(*func)(struct mdesc_handle *, u64, int, void *), void *arg, cpumask_t *mask)
{
	struct mdesc_handle *hp = mdesc_grab();
	void *ret = NULL;
	u64 mp;

	mdesc_for_each_node_by_name(hp, mp, "STR") {
		const u64 *id = mdesc_get_property(hp, mp, "STR", NULL);
		int cpuid = *id;

#ifdef CONFIG_SMP
		if (cpuid >= NR_CPUS) {
			printk(KERN_WARNING "STR"
			       "STR",
			       cpuid, NR_CPUS);
			continue;
		}
		if (!cpumask_test_cpu(cpuid, mask))
			continue;
#endif

		ret = func(hp, mp, cpuid, arg);
		if (ret)
			goto out;
	}
out:
	mdesc_release(hp);
	return ret;
}