PHP_FUNCTION(sqlite_popen)
{
	long mode = 0666;
	char *filename, *fullpath, *hashkey;
	int filename_len, hashkeylen;
	zval *errmsg = NULL;
	struct php_sqlite_db *db = NULL;
	zend_rsrc_list_entry *le;

	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "STR",
				&filename, &filename_len, &mode, &errmsg)) {
		return;
	}
	if (errmsg) {
		zval_dtor(errmsg);
		ZVAL_NULL(errmsg);
	}

	if (strncmp(filename, "STR") - 1)) {
		
		if (!(fullpath = expand_filepath(filename, NULL TSRMLS_CC))) {
			RETURN_FALSE;
		}

		if ((PG(safe_mode) && (!php_checkuid(fullpath, NULL, CHECKUID_CHECK_FILE_AND_DIR))) || 
				php_check_open_basedir(fullpath TSRMLS_CC)) {
			efree(fullpath);
			RETURN_FALSE;
		}
	} else {
		fullpath = estrndup(filename, filename_len);
	}

	hashkeylen = spprintf(&hashkey, 0, "STR", fullpath, mode);

	
	if (SUCCESS == zend_hash_find(&EG(persistent_list), hashkey, hashkeylen+1, (void*)&le)) {
		if (Z_TYPE_P(le) == le_sqlite_pdb) {
			db = (struct php_sqlite_db*)le->ptr;

			if (db->rsrc_id == FAILURE) {
				
				db->rsrc_id = ZEND_REGISTER_RESOURCE(return_value, db, le_sqlite_pdb);
			} else {
				int type;
				
				if (zend_list_find(db->rsrc_id, &type) == db) {
					
					zend_list_addref(db->rsrc_id);
					ZVAL_RESOURCE(return_value, db->rsrc_id);
				} else {
					db->rsrc_id = ZEND_REGISTER_RESOURCE(return_value, db, le_sqlite_pdb);
				}
			}

			
			goto done;
		}

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "STR");
		RETVAL_FALSE;
		goto done;
	}

	
	php_sqlite_open(fullpath, (int)mode, hashkey, return_value, errmsg, NULL TSRMLS_CC);
done:
	efree(fullpath);
	efree(hashkey);
}