PHPAPI void php_var_export(zval **struc, int level TSRMLS_DC) 
{
	smart_str buf = {0};
	php_var_export_ex(struc, level, &buf TSRMLS_CC);
	smart_str_0 (&buf);
	PHPWRITE(buf.c, buf.len);
	smart_str_free(&buf);
}