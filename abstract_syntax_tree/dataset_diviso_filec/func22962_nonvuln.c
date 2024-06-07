static int __init soc_bus_register(void)
{
	int ret;

	ret = bus_register(&soc_bus_type);
	if (ret)
		return ret;

	if (early_soc_dev_attr)
		return PTR_ERR(soc_device_register(early_soc_dev_attr));

	return 0;
}