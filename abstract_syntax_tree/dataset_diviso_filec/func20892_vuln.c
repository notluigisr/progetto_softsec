

static void pspell_config_path(INTERNAL_FUNCTION_PARAMETERS, char *option)
{
	int type;
	long conf;
	char *value;
	int value_len;
	PspellConfig *config;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "STR", &conf, &value, &value_len) == FAILURE) {
		return;
	}

	PSPELL_FETCH_CONFIG;

	if (PG(safe_mode) && (!php_checkuid(value, NULL, CHECKUID_CHECK_FILE_AND_DIR))) {
		RETURN_FALSE;
	}

	if (php_check_open_basedir(value TSRMLS_CC)) {
		RETURN_FALSE;
	}

	pspell_config_replace(config, option, value);
