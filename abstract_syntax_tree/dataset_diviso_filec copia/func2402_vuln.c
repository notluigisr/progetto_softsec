static int phar_tar_process_metadata(phar_entry_info *entry, php_stream *fp TSRMLS_DC) 
{
	char *metadata;
	size_t save = php_stream_tell(fp), read;
	phar_entry_info *mentry;

	metadata = (char *) emalloc(entry->uncompressed_filesize + 1);

	read = php_stream_read(fp, metadata, entry->uncompressed_filesize);
	if (read != entry->uncompressed_filesize) {
		efree(metadata);
		php_stream_seek(fp, save, SEEK_SET);
		return FAILURE;
	}

	if (phar_parse_metadata(&metadata, &entry->metadata, entry->uncompressed_filesize TSRMLS_CC) == FAILURE) {
		
		efree(metadata);
		php_stream_seek(fp, save, SEEK_SET);
		return FAILURE;
	}

	if (entry->filename_len == sizeof("STR")-1)) {
		entry->phar->metadata = entry->metadata;
		entry->metadata = NULL;
	} else if (entry->filename_len >= sizeof("STR") - 1), (void *)&mentry)) {
		
		mentry->metadata = entry->metadata;
		entry->metadata = NULL;
	}

	efree(metadata);
	php_stream_seek(fp, save, SEEK_SET);
	return SUCCESS;
}