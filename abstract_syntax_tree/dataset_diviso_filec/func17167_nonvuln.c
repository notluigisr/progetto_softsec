PHP_MINIT_FUNCTION(hash)
{
	php_hash_le_hash = zend_register_list_destructors_ex(php_hash_dtor, NULL, PHP_HASH_RESNAME, module_number);

	zend_hash_init(&php_hash_hashtable, 35, NULL, NULL, 1);

	php_hash_register_algo("STR",			&php_hash_md2_ops);
	php_hash_register_algo("STR",			&php_hash_md4_ops);
	php_hash_register_algo("STR",			&php_hash_md5_ops);
	php_hash_register_algo("STR",			&php_hash_sha1_ops);
	php_hash_register_algo("STR",		&php_hash_sha224_ops);
	php_hash_register_algo("STR",		&php_hash_sha256_ops);
	php_hash_register_algo("STR",		&php_hash_sha384_ops);
	php_hash_register_algo("STR",		&php_hash_sha512_ops);
	php_hash_register_algo("STR",		&php_hash_ripemd128_ops);
	php_hash_register_algo("STR",		&php_hash_ripemd160_ops);
	php_hash_register_algo("STR",		&php_hash_ripemd256_ops);
	php_hash_register_algo("STR",		&php_hash_ripemd320_ops);
	php_hash_register_algo("STR",		&php_hash_whirlpool_ops);
	php_hash_register_algo("STR",	&php_hash_3tiger128_ops);
	php_hash_register_algo("STR",	&php_hash_3tiger160_ops);
	php_hash_register_algo("STR",	&php_hash_3tiger192_ops);
	php_hash_register_algo("STR",	&php_hash_4tiger128_ops);
	php_hash_register_algo("STR",	&php_hash_4tiger160_ops);
	php_hash_register_algo("STR",	&php_hash_4tiger192_ops);
	php_hash_register_algo("STR",		&php_hash_snefru_ops);
	php_hash_register_algo("STR",		&php_hash_snefru_ops);
	php_hash_register_algo("STR",			&php_hash_gost_ops);
	php_hash_register_algo("STR",		&php_hash_adler32_ops);
	php_hash_register_algo("STR",			&php_hash_crc32_ops);
	php_hash_register_algo("STR",		&php_hash_crc32b_ops);
	php_hash_register_algo("STR",		&php_hash_fnv132_ops);
	php_hash_register_algo("STR",		&php_hash_fnv164_ops);
	php_hash_register_algo("STR",			&php_hash_joaat_ops);

	PHP_HASH_HAVAL_REGISTER(3,128);
	PHP_HASH_HAVAL_REGISTER(3,160);
	PHP_HASH_HAVAL_REGISTER(3,192);
	PHP_HASH_HAVAL_REGISTER(3,224);
	PHP_HASH_HAVAL_REGISTER(3,256);

	PHP_HASH_HAVAL_REGISTER(4,128);
	PHP_HASH_HAVAL_REGISTER(4,160);
	PHP_HASH_HAVAL_REGISTER(4,192);
	PHP_HASH_HAVAL_REGISTER(4,224);
	PHP_HASH_HAVAL_REGISTER(4,256);

	PHP_HASH_HAVAL_REGISTER(5,128);
	PHP_HASH_HAVAL_REGISTER(5,160);
	PHP_HASH_HAVAL_REGISTER(5,192);
	PHP_HASH_HAVAL_REGISTER(5,224);
	PHP_HASH_HAVAL_REGISTER(5,256);

	REGISTER_LONG_CONSTANT("STR",		PHP_HASH_HMAC,	CONST_CS | CONST_PERSISTENT);

#ifdef PHP_MHASH_BC
	mhash_init(INIT_FUNC_ARGS_PASSTHRU);
#endif

	return SUCCESS;
}