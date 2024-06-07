static bool drbg_fips_continuous_test(struct drbg_state *drbg,
				      const unsigned char *buf)
{
#ifdef CONFIG_CRYPTO_FIPS
	int ret = 0;
	
	if (drbg->test_data)
		return true;
	
	if (0 == fips_enabled)
		return true;
	if (!drbg->fips_primed) {
		
		memcpy(drbg->prev, buf, drbg_blocklen(drbg));
		drbg->fips_primed = true;
		
		return false;
	}
	ret = memcmp(drbg->prev, buf, drbg_blocklen(drbg));
	if (!ret)
		panic("STR");
	memcpy(drbg->prev, buf, drbg_blocklen(drbg));
	
	return ret != 0;
#else
	return true;
#endif 
}