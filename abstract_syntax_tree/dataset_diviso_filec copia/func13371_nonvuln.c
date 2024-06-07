PHP_METHOD(PharFileInfo, decompress)
{
	char *error;
	PHAR_ENTRY_OBJECT();

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	if (entry_obj->ent.entry->is_dir) {
		zend_throw_exception_ex(spl_ce_BadMethodCallException, 0 TSRMLS_CC, \
			"STR"); \
		return;
	}

	if ((entry_obj->ent.entry->flags & PHAR_ENT_COMPRESSION_MASK) == 0) {
		RETURN_TRUE;
	}

	if (PHAR_G(readonly) && !entry_obj->ent.entry->phar->is_data) {
		zend_throw_exception_ex(spl_ce_BadMethodCallException, 0 TSRMLS_CC,
			"STR");
		return;
	}

	if (entry_obj->ent.entry->is_deleted) {
		zend_throw_exception_ex(spl_ce_BadMethodCallException, 0 TSRMLS_CC,
			"STR");
		return;
	}

	if ((entry_obj->ent.entry->flags & PHAR_ENT_COMPRESSED_GZ) != 0 && !PHAR_G(has_zlib)) {
		zend_throw_exception_ex(spl_ce_BadMethodCallException, 0 TSRMLS_CC,
			"STR");
		return;
	}

	if ((entry_obj->ent.entry->flags & PHAR_ENT_COMPRESSED_BZ2) != 0 && !PHAR_G(has_bz2)) {
		zend_throw_exception_ex(spl_ce_BadMethodCallException, 0 TSRMLS_CC,
			"STR");
		return;
	}

	if (entry_obj->ent.entry->is_persistent) {
		phar_archive_data *phar = entry_obj->ent.entry->phar;

		if (FAILURE == phar_copy_on_write(&phar TSRMLS_CC)) {
			zend_throw_exception_ex(phar_ce_PharException, 0 TSRMLS_CC, "STR", phar->fname);
			return;
		}
		
		zend_hash_find(&phar->manifest, entry_obj->ent.entry->filename, entry_obj->ent.entry->filename_len, (void **)&entry_obj->ent.entry);
	}
	if (!entry_obj->ent.entry->fp) {
		if (FAILURE == phar_open_archive_fp(entry_obj->ent.entry->phar TSRMLS_CC)) {
			zend_throw_exception_ex(spl_ce_BadMethodCallException, 0 TSRMLS_CC, "STR", entry_obj->ent.entry->filename, entry_obj->ent.entry->phar->fname);
			return;
		}
		entry_obj->ent.entry->fp_type = PHAR_FP;
	}

	entry_obj->ent.entry->old_flags = entry_obj->ent.entry->flags;
	entry_obj->ent.entry->flags &= ~PHAR_ENT_COMPRESSION_MASK;
	entry_obj->ent.entry->phar->is_modified = 1;
	entry_obj->ent.entry->is_modified = 1;
	phar_flush(entry_obj->ent.entry->phar, 0, 0, 0, &error TSRMLS_CC);

	if (error) {
		zend_throw_exception_ex(phar_ce_PharException, 0 TSRMLS_CC, "STR", error);
		efree(error);
	}
	RETURN_TRUE;
}