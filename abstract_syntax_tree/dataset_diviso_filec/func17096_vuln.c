static PHP_FUNCTION(bzdecompress)
{
	char *source, *dest;
	int source_len, error;
	long small = 0;
#if defined(PHP_WIN32)
	unsigned __int64 size = 0;
#else
	unsigned long long size = 0;
#endif
	bz_stream bzs;

	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "STR", &source, &source_len, &small)) {
		RETURN_FALSE;
	}

	bzs.bzalloc = NULL;
	bzs.bzfree = NULL;

	if (BZ2_bzDecompressInit(&bzs, 0, small) != BZ_OK) {
		RETURN_FALSE;
	}

	bzs.next_in = source;
	bzs.avail_in = source_len;

	
	bzs.avail_out = source_len * 2;
	bzs.next_out = dest = emalloc(bzs.avail_out + 1);
	
	while ((error = BZ2_bzDecompress(&bzs)) == BZ_OK && bzs.avail_in > 0) {
		
		bzs.avail_out = source_len;
		size = (bzs.total_out_hi32 * (unsigned int) -1) + bzs.total_out_lo32;
		dest = safe_erealloc(dest, 1, bzs.avail_out+1, (size_t) size );
		bzs.next_out = dest + size;
	}

	if (error == BZ_STREAM_END || error == BZ_OK) {
		size = (bzs.total_out_hi32 * (unsigned int) -1) + bzs.total_out_lo32;
		dest = safe_erealloc(dest, 1, (size_t) size, 1);
		dest[size] = '\0';
		RETVAL_STRINGL(dest, (int) size, 0);
	} else { 
		efree(dest);
		RETVAL_LONG(error);
	}

	BZ2_bzDecompressEnd(&bzs);
}