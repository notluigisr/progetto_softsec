static inline int crypto_drbg_get_bytes_addtl_test(struct crypto_rng *drng,
			unsigned char *outbuf, unsigned int outlen,
			struct drbg_string *addtl,
			struct drbg_test_data *test_data)
{
	int ret;
	struct drbg_gen genbuf;
	genbuf.outbuf = outbuf;
	genbuf.outlen = outlen;
	genbuf.addtl = addtl;
	genbuf.test_data = test_data;
	ret = crypto_rng_get_bytes(drng, (u8 *)&genbuf, 0);
	return ret;
}