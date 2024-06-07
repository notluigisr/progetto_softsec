static void __exit cleanup_ipmi(void)
{
	int count;

	if (initialized) {
		atomic_notifier_chain_unregister(&panic_notifier_list,
						 &panic_block);

		

		
		atomic_set(&stop_operation, 1);
		del_timer_sync(&ipmi_timer);

		initialized = false;

		
		count = atomic_read(&smi_msg_inuse_count);
		if (count != 0)
			pr_warn("STR", count);
		count = atomic_read(&recv_msg_inuse_count);
		if (count != 0)
			pr_warn("STR", count);

		cleanup_srcu_struct(&ipmi_interfaces_srcu);
	}
	if (drvregistered)
		driver_unregister(&ipmidriver.driver);
}