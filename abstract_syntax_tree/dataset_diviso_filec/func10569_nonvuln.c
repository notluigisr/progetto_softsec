static int svm_cpu_init(int cpu)
{
	struct svm_cpu_data *sd;
	int ret = -ENOMEM;

	sd = kzalloc(sizeof(struct svm_cpu_data), GFP_KERNEL);
	if (!sd)
		return ret;
	sd->cpu = cpu;
	sd->save_area = alloc_page(GFP_KERNEL);
	if (!sd->save_area)
		goto free_cpu_data;

	clear_page(page_address(sd->save_area));

	ret = sev_cpu_init(sd);
	if (ret)
		goto free_save_area;

	per_cpu(svm_data, cpu) = sd;

	return 0;

free_save_area:
	__free_page(sd->save_area);
free_cpu_data:
	kfree(sd);
	return ret;

}