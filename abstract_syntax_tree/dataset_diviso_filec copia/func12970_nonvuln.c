static int tcm_loop_alloc_core_bus(void)
{
	int ret;

	tcm_loop_primary = root_device_register("STR");
	if (IS_ERR(tcm_loop_primary)) {
		printk(KERN_ERR "STR");
		return PTR_ERR(tcm_loop_primary);
	}

	ret = bus_register(&tcm_loop_lld_bus);
	if (ret) {
		printk(KERN_ERR "STR");
		goto dev_unreg;
	}

	ret = driver_register(&tcm_loop_driverfs);
	if (ret) {
		printk(KERN_ERR "STR"
				"STR");
		goto bus_unreg;
	}

	printk(KERN_INFO "STR");
	return ret;

bus_unreg:
	bus_unregister(&tcm_loop_lld_bus);
dev_unreg:
	root_device_unregister(tcm_loop_primary);
	return ret;
}