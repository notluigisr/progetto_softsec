static inline void init_keys(at91_aes_key_size_t *key_size,
			     unsigned int *cipher_key,
			     unsigned int *cmac_key,
			     unsigned int *iv)
{
#if defined(CONFIG_AES_KEY_SIZE_128)
	*key_size = AT91_AES_KEY_SIZE_128;
#elif defined(CONFIG_AES_KEY_SIZE_192)
	*key_size = AT91_AES_KEY_SIZE_192;
#elif defined(CONFIG_AES_KEY_SIZE_256)
	*key_size = AT91_AES_KEY_SIZE_256;
#else
#error "STR"
#endif

	iv[0]		= CONFIG_AES_IV_WORD0;
	iv[1]		= CONFIG_AES_IV_WORD1;
	iv[2]		= CONFIG_AES_IV_WORD2;
	iv[3]		= CONFIG_AES_IV_WORD3;

	cipher_key[0]	= CONFIG_AES_CIPHER_KEY_WORD0;
	cmac_key[0]	= CONFIG_AES_CMAC_KEY_WORD0;
	cipher_key[1]	= CONFIG_AES_CIPHER_KEY_WORD1;
	cmac_key[1]	= CONFIG_AES_CMAC_KEY_WORD1;
	cipher_key[2]	= CONFIG_AES_CIPHER_KEY_WORD2;
	cmac_key[2]	= CONFIG_AES_CMAC_KEY_WORD2;
	cipher_key[3]	= CONFIG_AES_CIPHER_KEY_WORD3;
	cmac_key[3]	= CONFIG_AES_CMAC_KEY_WORD3;

#if defined(CONFIG_AES_KEY_SIZE_192) || defined(CONFIG_AES_KEY_SIZE_256)
	cipher_key[4]	= CONFIG_AES_CIPHER_KEY_WORD4;
	cmac_key[4]	= CONFIG_AES_CMAC_KEY_WORD4;
	cipher_key[5]	= CONFIG_AES_CIPHER_KEY_WORD5;
	cmac_key[5]	= CONFIG_AES_CMAC_KEY_WORD5;
#endif

#if defined(CONFIG_AES_KEY_SIZE_256)
	cipher_key[6]	= CONFIG_AES_CIPHER_KEY_WORD6;
	cmac_key[6]	= CONFIG_AES_CMAC_KEY_WORD6;
	cipher_key[7]	= CONFIG_AES_CIPHER_KEY_WORD7;
	cmac_key[7]	= CONFIG_AES_CMAC_KEY_WORD7;
#endif
}