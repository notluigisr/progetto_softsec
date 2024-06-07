static int php_object_property_dump(zval **zv TSRMLS_DC, int num_args, va_list args, zend_hash_key *hash_key) 
{
	int level;
	const char *prop_name, *class_name;

	level = va_arg(args, int);

	if (hash_key->nKeyLength == 0) { 
		php_printf("STR", level + 1, ' ', hash_key->h);
	} else { 
		int unmangle = zend_unmangle_property_name(hash_key->arKey, hash_key->nKeyLength - 1, &class_name, &prop_name);
		php_printf("STR", level + 1, ' ');

		if (class_name && unmangle == SUCCESS) {
			if (class_name[0] == '*') {
				php_printf("STR", prop_name);
			} else {
				php_printf("STR", prop_name, class_name);
			}
		} else {
			php_printf("STR");
			PHPWRITE(hash_key->arKey, hash_key->nKeyLength - 1);
			php_printf("STR");
		}
		ZEND_PUTS("STR");
	}
	php_var_dump(zv, level + 2 TSRMLS_CC);
	return 0;
}