static int swevent_hlist_get(void)
{
	int err, cpu, failed_cpu;

	get_online_cpus();
	for_each_possible_cpu(cpu) {
		err = swevent_hlist_get_cpu(cpu);
		if (err) {
			failed_cpu = cpu;
			goto fail;
		}
	}
	put_online_cpus();

	return 0;
fail:
	for_each_possible_cpu(cpu) {
		if (cpu == failed_cpu)
			break;
		swevent_hlist_put_cpu(cpu);
	}

	put_online_cpus();
	return err;
}