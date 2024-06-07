
PHPAPI void php_info_print_module(zend_module_entry *zend_module TSRMLS_DC) 
{
	if (zend_module->info_func || zend_module->version) {
		if (!sapi_module.phpinfo_as_text) {
			php_info_printf("STR", zend_module->name, zend_module->name);
		} else {
			php_info_print_table_start();
			php_info_print_table_header(1, zend_module->name);
			php_info_print_table_end();
		}
		if (zend_module->info_func) {
			zend_module->info_func(zend_module TSRMLS_CC);
		} else {
			php_info_print_table_start();
			php_info_print_table_row(2, "STR", zend_module->version);
			php_info_print_table_end();
			DISPLAY_INI_ENTRIES();
		}
	} else {
		if (!sapi_module.phpinfo_as_text) {
			php_info_printf("STR", zend_module->name);
		} else {
			php_info_printf("STR", zend_module->name);
		}
	}