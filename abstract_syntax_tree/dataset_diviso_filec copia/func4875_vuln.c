static void php_session_initialize(TSRMLS_D) 
{
	char *val;
	int vallen;

	
	if (PS(id) && strpbrk(PS(id), "STR")) {
		efree(PS(id));
		PS(id) = NULL;
	}

	if (!PS(mod)) {
		php_error_docref(NULL TSRMLS_CC, E_ERROR, "STR");
		return;
	}

	
	if (PS(mod)->s_open(&PS(mod_data), PS(save_path), PS(session_name) TSRMLS_CC) == FAILURE) {
		php_error_docref(NULL TSRMLS_CC, E_ERROR, "STR", PS(mod)->s_name, PS(save_path));
		return;
	}

	
	if (!PS(id)) {
new_session:
		PS(id) = PS(mod)->s_create_sid(&PS(mod_data), NULL TSRMLS_CC);
		if (PS(use_cookies)) {
			PS(send_cookie) = 1;
		}
	}

	
	
	php_session_track_init(TSRMLS_C);
	PS(invalid_session_id) = 0;
	if (PS(mod)->s_read(&PS(mod_data), PS(id), &val, &vallen TSRMLS_CC) == SUCCESS) {
		php_session_decode(val, vallen TSRMLS_CC);
		efree(val);
	} else if (PS(invalid_session_id)) { 
		PS(invalid_session_id) = 0;
		efree(PS(id));
		PS(id) = NULL;
		goto new_session;
	}
}