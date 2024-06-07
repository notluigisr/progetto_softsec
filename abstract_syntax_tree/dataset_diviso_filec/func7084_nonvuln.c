static int sev_flush_asids(void)
{
	int ret, error = 0;

	
	down_write(&sev_deactivate_lock);

	wbinvd_on_all_cpus();
	ret = sev_guest_df_flush(&error);

	up_write(&sev_deactivate_lock);

	if (ret)
		pr_err("STR", ret, error);

	return ret;
}