static void php_imagefontsize(INTERNAL_FUNCTION_PARAMETERS, int arg)
{
	long SIZE;
	gdFontPtr font;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "STR", &SIZE) == FAILURE) {
		return;
	}

	font = php_find_gd_font(SIZE TSRMLS_CC);
	RETURN_LONG(arg ? font->h : font->w);
}