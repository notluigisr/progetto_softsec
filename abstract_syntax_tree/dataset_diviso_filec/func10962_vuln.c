void OpenSSL_add_all_ciphers(void)
	{

#ifndef OPENSSL_NO_DES
	EVP_add_cipher(EVP_des_cfb());
	EVP_add_cipher(EVP_des_cfb1());
	EVP_add_cipher(EVP_des_cfb8());
	EVP_add_cipher(EVP_des_ede_cfb());
	EVP_add_cipher(EVP_des_ede3_cfb());
	EVP_add_cipher(EVP_des_ede3_cfb1());
	EVP_add_cipher(EVP_des_ede3_cfb8());

	EVP_add_cipher(EVP_des_ofb());
	EVP_add_cipher(EVP_des_ede_ofb());
	EVP_add_cipher(EVP_des_ede3_ofb());

	EVP_add_cipher(EVP_desx_cbc());
	EVP_add_cipher_alias(SN_desx_cbc,"STR");
	EVP_add_cipher_alias(SN_desx_cbc,"STR");

	EVP_add_cipher(EVP_des_cbc());
	EVP_add_cipher_alias(SN_des_cbc,"STR");
	EVP_add_cipher_alias(SN_des_cbc,"STR");
	EVP_add_cipher(EVP_des_ede_cbc());
	EVP_add_cipher(EVP_des_ede3_cbc());
	EVP_add_cipher_alias(SN_des_ede3_cbc,"STR");
	EVP_add_cipher_alias(SN_des_ede3_cbc,"STR");

	EVP_add_cipher(EVP_des_ecb());
	EVP_add_cipher(EVP_des_ede());
	EVP_add_cipher(EVP_des_ede3());
#endif

#ifndef OPENSSL_NO_RC4
	EVP_add_cipher(EVP_rc4());
	EVP_add_cipher(EVP_rc4_40());
#endif

#ifndef OPENSSL_NO_IDEA
	EVP_add_cipher(EVP_idea_ecb());
	EVP_add_cipher(EVP_idea_cfb());
	EVP_add_cipher(EVP_idea_ofb());
	EVP_add_cipher(EVP_idea_cbc());
	EVP_add_cipher_alias(SN_idea_cbc,"STR");
	EVP_add_cipher_alias(SN_idea_cbc,"STR");
#endif

#ifndef OPENSSL_NO_SEED
	EVP_add_cipher(EVP_seed_ecb());
	EVP_add_cipher(EVP_seed_cfb());
	EVP_add_cipher(EVP_seed_ofb());
	EVP_add_cipher(EVP_seed_cbc());
	EVP_add_cipher_alias(SN_seed_cbc,"STR");
	EVP_add_cipher_alias(SN_seed_cbc,"STR");
#endif

#ifndef OPENSSL_NO_RC2
	EVP_add_cipher(EVP_rc2_ecb());
	EVP_add_cipher(EVP_rc2_cfb());
	EVP_add_cipher(EVP_rc2_ofb());
	EVP_add_cipher(EVP_rc2_cbc());
	EVP_add_cipher(EVP_rc2_40_cbc());
	EVP_add_cipher(EVP_rc2_64_cbc());
	EVP_add_cipher_alias(SN_rc2_cbc,"STR");
	EVP_add_cipher_alias(SN_rc2_cbc,"STR");
#endif

#ifndef OPENSSL_NO_BF
	EVP_add_cipher(EVP_bf_ecb());
	EVP_add_cipher(EVP_bf_cfb());
	EVP_add_cipher(EVP_bf_ofb());
	EVP_add_cipher(EVP_bf_cbc());
	EVP_add_cipher_alias(SN_bf_cbc,"STR");
	EVP_add_cipher_alias(SN_bf_cbc,"STR");
	EVP_add_cipher_alias(SN_bf_cbc,"STR");
#endif

#ifndef OPENSSL_NO_CAST
	EVP_add_cipher(EVP_cast5_ecb());
	EVP_add_cipher(EVP_cast5_cfb());
	EVP_add_cipher(EVP_cast5_ofb());
	EVP_add_cipher(EVP_cast5_cbc());
	EVP_add_cipher_alias(SN_cast5_cbc,"STR");
	EVP_add_cipher_alias(SN_cast5_cbc,"STR");
	EVP_add_cipher_alias(SN_cast5_cbc,"STR");
	EVP_add_cipher_alias(SN_cast5_cbc,"STR");
#endif

#ifndef OPENSSL_NO_RC5
	EVP_add_cipher(EVP_rc5_32_12_16_ecb());
	EVP_add_cipher(EVP_rc5_32_12_16_cfb());
	EVP_add_cipher(EVP_rc5_32_12_16_ofb());
	EVP_add_cipher(EVP_rc5_32_12_16_cbc());
	EVP_add_cipher_alias(SN_rc5_cbc,"STR");
	EVP_add_cipher_alias(SN_rc5_cbc,"STR");
#endif

#ifndef OPENSSL_NO_AES
	EVP_add_cipher(EVP_aes_128_ecb());
	EVP_add_cipher(EVP_aes_128_cbc());
	EVP_add_cipher(EVP_aes_128_cfb());
	EVP_add_cipher(EVP_aes_128_cfb1());
	EVP_add_cipher(EVP_aes_128_cfb8());
	EVP_add_cipher(EVP_aes_128_ofb());
#if 0
	EVP_add_cipher(EVP_aes_128_ctr());
#endif
	EVP_add_cipher_alias(SN_aes_128_cbc,"STR");
	EVP_add_cipher_alias(SN_aes_128_cbc,"STR");
	EVP_add_cipher(EVP_aes_192_ecb());
	EVP_add_cipher(EVP_aes_192_cbc());
	EVP_add_cipher(EVP_aes_192_cfb());
	EVP_add_cipher(EVP_aes_192_cfb1());
	EVP_add_cipher(EVP_aes_192_cfb8());
	EVP_add_cipher(EVP_aes_192_ofb());
#if 0
	EVP_add_cipher(EVP_aes_192_ctr());
#endif
	EVP_add_cipher_alias(SN_aes_192_cbc,"STR");
	EVP_add_cipher_alias(SN_aes_192_cbc,"STR");
	EVP_add_cipher(EVP_aes_256_ecb());
	EVP_add_cipher(EVP_aes_256_cbc());
	EVP_add_cipher(EVP_aes_256_cfb());
	EVP_add_cipher(EVP_aes_256_cfb1());
	EVP_add_cipher(EVP_aes_256_cfb8());
	EVP_add_cipher(EVP_aes_256_ofb());
#if 0
	EVP_add_cipher(EVP_aes_256_ctr());
#endif
	EVP_add_cipher_alias(SN_aes_256_cbc,"STR");
	EVP_add_cipher_alias(SN_aes_256_cbc,"STR");
#endif

#ifndef OPENSSL_NO_CAMELLIA
	EVP_add_cipher(EVP_camellia_128_ecb());
	EVP_add_cipher(EVP_camellia_128_cbc());
	EVP_add_cipher(EVP_camellia_128_cfb());
	EVP_add_cipher(EVP_camellia_128_cfb1());
	EVP_add_cipher(EVP_camellia_128_cfb8());
	EVP_add_cipher(EVP_camellia_128_ofb());
	EVP_add_cipher_alias(SN_camellia_128_cbc,"STR");
	EVP_add_cipher_alias(SN_camellia_128_cbc,"STR");
	EVP_add_cipher(EVP_camellia_192_ecb());
	EVP_add_cipher(EVP_camellia_192_cbc());
	EVP_add_cipher(EVP_camellia_192_cfb());
	EVP_add_cipher(EVP_camellia_192_cfb1());
	EVP_add_cipher(EVP_camellia_192_cfb8());
	EVP_add_cipher(EVP_camellia_192_ofb());
	EVP_add_cipher_alias(SN_camellia_192_cbc,"STR");
	EVP_add_cipher_alias(SN_camellia_192_cbc,"STR");
	EVP_add_cipher(EVP_camellia_256_ecb());
	EVP_add_cipher(EVP_camellia_256_cbc());
	EVP_add_cipher(EVP_camellia_256_cfb());
	EVP_add_cipher(EVP_camellia_256_cfb1());
	EVP_add_cipher(EVP_camellia_256_cfb8());
	EVP_add_cipher(EVP_camellia_256_ofb());
	EVP_add_cipher_alias(SN_camellia_256_cbc,"STR");
	EVP_add_cipher_alias(SN_camellia_256_cbc,"STR");
#endif

	PKCS12_PBE_add();
	PKCS5_PBE_add();
	}