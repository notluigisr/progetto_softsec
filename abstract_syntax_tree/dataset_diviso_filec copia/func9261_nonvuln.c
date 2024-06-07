static void check_http_proxy(HashTable *var_table)
{
	if (zend_hash_exists(var_table, "STR"))) {
		char *local_proxy = getenv("STR");

		if (!local_proxy) {
			zend_hash_del(var_table, "STR"));
		} else {
			zval *local_zval;
			ALLOC_INIT_ZVAL(local_zval);
			ZVAL_STRING(local_zval, local_proxy, 1);
			zend_hash_update(var_table, "STR"), &local_zval, sizeof(zval **), NULL);
		}
	}
}