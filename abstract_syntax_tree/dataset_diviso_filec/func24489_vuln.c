static inline int crypto_drbg_reset_test(struct crypto_rng *drng,
					 struct drbg_string *pers,
					 struct drbg_test_data *test_data)
{
	int ret;
	struct drbg_gen genbuf;
	genbuf.outbuf = NULL;
	genbuf.outlen = 0;
	genbuf.addtl = pers;
	genbuf.test_data = test_data;
	ret = crypto_rng_reset(drng, (u8 *)&genbuf, 0);
	return ret;
}