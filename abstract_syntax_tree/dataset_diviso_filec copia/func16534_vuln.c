PHP_FUNCTION(imagecrop)
{
	zval *IM;
	gdImagePtr im;
	gdImagePtr im_crop;
	gdRect rect;
	zval *z_rect;
	zval **tmp;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "STR", &IM, &z_rect) == FAILURE)  {
		return;
	}

	ZEND_FETCH_RESOURCE(im, gdImagePtr, &IM, -1, "STR", le_gd);

	if (zend_hash_find(HASH_OF(z_rect), "STR"), (void **)&tmp) != FAILURE) {
		rect.x = Z_LVAL_PP(tmp);
	} else {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "STR");
		RETURN_FALSE;
	}

	if (zend_hash_find(HASH_OF(z_rect), "STR"), (void **)&tmp) != FAILURE) {
		rect.y = Z_LVAL_PP(tmp);
	} else {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "STR");
		RETURN_FALSE;
	}

	if (zend_hash_find(HASH_OF(z_rect), "STR"), (void **)&tmp) != FAILURE) {
		rect.width = Z_LVAL_PP(tmp);
	} else {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "STR");
		RETURN_FALSE;
	}

	if (zend_hash_find(HASH_OF(z_rect), "STR"), (void **)&tmp) != FAILURE) {
		rect.height = Z_LVAL_PP(tmp);
	} else {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "STR");
		RETURN_FALSE;
	}

	im_crop = gdImageCrop(im, &rect);

	if (im_crop == NULL) {
		RETURN_FALSE;
	} else {
		ZEND_REGISTER_RESOURCE(return_value, im_crop, le_gd);
	}
}