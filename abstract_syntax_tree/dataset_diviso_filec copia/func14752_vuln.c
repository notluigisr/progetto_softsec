static int phar_tar_setupmetadata(void *pDest, void *argument TSRMLS_DC) 
{
	int lookfor_len;
	struct _phar_pass_tar_info *i = (struct _phar_pass_tar_info *)argument;
	char *lookfor, **error = i->error;
	phar_entry_info *entry = (phar_entry_info *)pDest, *metadata, newentry = {0};

	if (entry->filename_len >= sizeof("STR")-1)) {
		if (entry->filename_len == sizeof("STR")-1)) {
			return phar_tar_setmetadata(entry->phar->metadata, entry, error TSRMLS_CC);
		}
		
		if (entry->filename_len >= sizeof("STR") - 1))) {
			
			return ZEND_HASH_APPLY_REMOVE;
		}
		
		return ZEND_HASH_APPLY_KEEP;
	}

	if (!entry->is_modified) {
		return ZEND_HASH_APPLY_KEEP;
	}

	
	lookfor_len = spprintf(&lookfor, 0, "STR", entry->filename);

	if (!entry->metadata) {
		zend_hash_del(&(entry->phar->manifest), lookfor, lookfor_len);
		efree(lookfor);
		return ZEND_HASH_APPLY_KEEP;
	}

	if (SUCCESS == zend_hash_find(&(entry->phar->manifest), lookfor, lookfor_len, (void **)&metadata)) {
		int ret;
		ret = phar_tar_setmetadata(entry->metadata, metadata, error TSRMLS_CC);
		efree(lookfor);
		return ret;
	}

	newentry.filename = lookfor;
	newentry.filename_len = lookfor_len;
	newentry.phar = entry->phar;
	newentry.tar_type = TAR_FILE;
	newentry.is_tar = 1;

	if (SUCCESS != zend_hash_add(&(entry->phar->manifest), lookfor, lookfor_len, (void *)&newentry, sizeof(phar_entry_info), (void **)&metadata)) {
		efree(lookfor);
		spprintf(error, 0, "STR", entry->filename);
		return ZEND_HASH_APPLY_STOP;
	}

	return phar_tar_setmetadata(entry->metadata, metadata, error TSRMLS_CC);
}