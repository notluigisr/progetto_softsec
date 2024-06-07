static void __exit drbg_exit(void)
{
	crypto_unregister_algs(drbg_algs, (ARRAY_SIZE(drbg_cores) * 2));
}