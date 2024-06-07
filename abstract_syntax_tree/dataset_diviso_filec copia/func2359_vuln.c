static void php_build_argv(char *s, zval *track_vars_array TSRMLS_DC)
{
	zval *arr, *argc, *tmp;
	int count = 0;
	char *ss, *space;
	
	if (!(SG(request_info).argc || track_vars_array)) {
		return;
	}
	
	ALLOC_INIT_ZVAL(arr);
	array_init(arr);

	
	if (SG(request_info).argc) { 
		int i;
		for (i = 0; i < SG(request_info).argc; i++) {
			ALLOC_ZVAL(tmp);
			Z_TYPE_P(tmp) = IS_STRING;
			Z_STRLEN_P(tmp) = strlen(SG(request_info).argv[i]);
			Z_STRVAL_P(tmp) = estrndup(SG(request_info).argv[i], Z_STRLEN_P(tmp));
			INIT_PZVAL(tmp);
			if (zend_hash_next_index_insert(Z_ARRVAL_P(arr), &tmp, sizeof(zval *), NULL) == FAILURE) {
				if (Z_TYPE_P(tmp) == IS_STRING) {
					efree(Z_STRVAL_P(tmp));
				}
			}
		}
	} else 	if (s && *s) {
		ss = s;
		while (ss) {
			space = strchr(ss, '+');
			if (space) {
				*space = '\0';
			}
			
			ALLOC_ZVAL(tmp);
			Z_TYPE_P(tmp) = IS_STRING;
			Z_STRLEN_P(tmp) = strlen(ss);
			Z_STRVAL_P(tmp) = estrndup(ss, Z_STRLEN_P(tmp));
			INIT_PZVAL(tmp);
			count++;
			if (zend_hash_next_index_insert(Z_ARRVAL_P(arr), &tmp, sizeof(zval *), NULL) == FAILURE) {
				if (Z_TYPE_P(tmp) == IS_STRING) {
					efree(Z_STRVAL_P(tmp));
				}
			}
			if (space) {
				*space = '+';
				ss = space + 1;
			} else {
				ss = space;
			}
		}
	}

	
	ALLOC_INIT_ZVAL(argc);
	if (SG(request_info).argc) {
		Z_LVAL_P(argc) = SG(request_info).argc;
	} else {
		Z_LVAL_P(argc) = count;
	}
	Z_TYPE_P(argc) = IS_LONG;

	if (SG(request_info).argc) {
		Z_ADDREF_P(arr);
		Z_ADDREF_P(argc);
		zend_hash_update(&EG(symbol_table), "STR"), &arr, sizeof(zval *), NULL);
		zend_hash_update(&EG(symbol_table), "STR"), &argc, sizeof(zval *), NULL);
	} 
	if (track_vars_array) {
		Z_ADDREF_P(arr);
		Z_ADDREF_P(argc);
		zend_hash_update(Z_ARRVAL_P(track_vars_array), "STR"), &arr, sizeof(zval *), NULL);
		zend_hash_update(Z_ARRVAL_P(track_vars_array), "STR"), &argc, sizeof(zval *), NULL);
	}
	zval_ptr_dtor(&arr);
	zval_ptr_dtor(&argc);
}