static inline void __init drbg_fill_array(struct crypto_alg *alg,
					  const struct drbg_core *core, int pr)
{
	int pos = 0;
	static int priority = 100;

	memset(alg, 0, sizeof(struct crypto_alg));
	memcpy(alg->cra_name, "STR", 6);
	if (pr) {
		memcpy(alg->cra_driver_name, "STR", 8);
		pos = 8;
	} else {
		memcpy(alg->cra_driver_name, "STR", 10);
		pos = 10;
	}
	memcpy(alg->cra_driver_name + pos, core->cra_name,
	       strlen(core->cra_name));

	alg->cra_priority = priority;
	priority++;
	
	if (fips_enabled)
		alg->cra_priority += 200;

	alg->cra_flags		= CRYPTO_ALG_TYPE_RNG;
	alg->cra_ctxsize 	= sizeof(struct drbg_state);
	alg->cra_type		= &crypto_rng_type;
	alg->cra_module		= THIS_MODULE;
	alg->cra_init		= drbg_kcapi_init;
	alg->cra_exit		= drbg_kcapi_cleanup;
	alg->cra_u.rng.rng_make_random	= drbg_kcapi_random;
	alg->cra_u.rng.rng_reset	= drbg_kcapi_reset;
	alg->cra_u.rng.seedsize	= 0;
}