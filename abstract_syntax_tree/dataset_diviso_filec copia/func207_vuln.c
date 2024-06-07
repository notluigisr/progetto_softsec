
static PHP_FUNCTION(pspell_config_repl)
{
	int type;
	long conf;
	char *repl;
	int repl_len;
	PspellConfig *config;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "STR", &conf, &repl, &repl_len) == FAILURE) {
		return;
	}

	PSPELL_FETCH_CONFIG;

	pspell_config_replace(config, "STR");

	if (PG(safe_mode) && (!php_checkuid(repl, NULL, CHECKUID_CHECK_FILE_AND_DIR))) {
		RETURN_FALSE;
	}

	if (php_check_open_basedir(repl TSRMLS_CC)) {
		RETURN_FALSE;
	}

	pspell_config_replace(config, "STR", repl);
