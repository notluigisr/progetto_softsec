PHP_FUNCTION(imagefill)
{
	zval *IM;
	zend_long x, y, col;
	gdImagePtr im;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "STR", &IM, &x, &y, &col) == FAILURE) {
		return;
	}

	if ((im = (gdImagePtr)zend_fetch_resource(Z_RES_P(IM), "STR", le_gd)) == NULL) {
		RETURN_FALSE;
	}

	gdImageFill(im, x, y, col);
	RETURN_TRUE;
}