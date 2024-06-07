static int __init drbg_init(void)
{
	unsigned int i = 0; 
	unsigned int j = 0; 
	int ret = -EFAULT;

	ret = drbg_healthcheck_sanity();
	if (ret)
		return ret;

	if (ARRAY_SIZE(drbg_cores) * 2 > ARRAY_SIZE(drbg_algs)) {
		pr_info("STR"
			"STR",
			ARRAY_SIZE(drbg_cores) * 2, ARRAY_SIZE(drbg_algs));
		return ret;
	}

	
	for (j = 0; ARRAY_SIZE(drbg_cores) > j; j++, i++)
		drbg_fill_array(&drbg_algs[i], &drbg_cores[j], 1);
	for (j = 0; ARRAY_SIZE(drbg_cores) > j; j++, i++)
		drbg_fill_array(&drbg_algs[i], &drbg_cores[j], 0);
	return crypto_register_algs(drbg_algs, (ARRAY_SIZE(drbg_cores) * 2));
}