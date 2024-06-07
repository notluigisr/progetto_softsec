static int __rtas_suspend_last_cpu(struct rtas_suspend_me_data *data, int wake_when_done)
{
	u16 slb_size = mmu_slb_size;
	int rc = H_MULTI_THREADS_ACTIVE;
	int cpu;

	slb_set_size(SLB_MIN_SIZE);
	printk(KERN_DEBUG "STR", smp_processor_id());

	while (rc == H_MULTI_THREADS_ACTIVE && !atomic_read(&data->done) &&
	       !atomic_read(&data->error))
		rc = rtas_call(data->token, 0, 1, NULL);

	if (rc || atomic_read(&data->error)) {
		printk(KERN_DEBUG "STR", rc);
		slb_set_size(slb_size);
	}

	if (atomic_read(&data->error))
		rc = atomic_read(&data->error);

	atomic_set(&data->error, rc);
	pSeries_coalesce_init();

	if (wake_when_done) {
		atomic_set(&data->done, 1);

		for_each_online_cpu(cpu)
			plpar_hcall_norets(H_PROD, get_hard_smp_processor_id(cpu));
	}

	if (atomic_dec_return(&data->working) == 0)
		complete(data->complete);

	return rc;
}