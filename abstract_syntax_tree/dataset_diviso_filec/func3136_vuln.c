PHP_FUNCTION(imagetruecolortopalette)
{
	zval *IM;
	zend_bool dither;
	zend_long ncolors;
	gdImagePtr im;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "STR", &IM, &dither, &ncolors) == FAILURE)  {
		return;
	}

	if ((im = (gdImagePtr)zend_fetch_resource(Z_RES_P(IM), "STR", le_gd)) == NULL) {
		RETURN_FALSE;
	}

	if (ncolors <= 0) {
		php_error_docref(NULL, E_WARNING, "STR");
		RETURN_FALSE;
	}
	gdImageTrueColorToPalette(im, dither, ncolors);

	RETURN_TRUE;
}