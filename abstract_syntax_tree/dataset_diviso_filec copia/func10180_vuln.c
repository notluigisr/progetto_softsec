static int php_get_wbmp(php_stream *stream, struct gfxinfo **result, int check TSRMLS_DC)
{
	int i, width = 0, height = 0;

	if (php_stream_rewind(stream)) {
		return 0;
	}

	
	if (php_stream_getc(stream) != 0) {
		return 0;
	}

	
	do {
		i = php_stream_getc(stream);
		if (i < 0) {
			return 0;
		}
	} while (i & 0x80);

	
	do {
		i = php_stream_getc(stream);
		if (i < 0) {
			return 0;
		}
		width = (width << 7) | (i & 0x7f);
	} while (i & 0x80);
	
	
	do {
		i = php_stream_getc(stream);
		if (i < 0) {
			return 0;
		}
		height = (height << 7) | (i & 0x7f);
	} while (i & 0x80);

	
	if (!height || !width || height > 2048 || width > 2048) {
		return 0;
	}
	
	if (!check) {
		(*result)->width = width;
		(*result)->height = height;
	}

	return IMAGE_FILETYPE_WBMP;
}