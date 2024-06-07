static int FIPS_aes_test(void)
	{
	int ret = 0;
	unsigned char pltmp[16];
	unsigned char citmp[16];
	unsigned char key[16] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
	unsigned char plaintext[16] = "STR";
	EVP_CIPHER_CTX ctx;
	FIPS_cipher_ctx_init(&ctx);
	if (FIPS_cipherinit(&ctx, EVP_aes_128_ecb(), key, NULL, 1) <= 0)
		goto err;
	FIPS_cipher(&ctx, citmp, plaintext, 16);
	if (FIPS_cipherinit(&ctx, EVP_aes_128_ecb(), key, NULL, 0) <= 0)
		goto err;
	FIPS_cipher(&ctx, pltmp, citmp, 16);
	if (memcmp(pltmp, plaintext, 16))
		goto err;
	ret = 1;
	err:
	FIPS_cipher_ctx_cleanup(&ctx);
	return ret;
	}