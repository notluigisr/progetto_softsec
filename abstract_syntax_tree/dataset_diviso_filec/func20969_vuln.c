PHP_FUNCTION(imageconvolution)
{
	zval *SIM, *hash_matrix;
	zval **var = NULL, **var2 = NULL;
	gdImagePtr im_src = NULL;
	double div, offset;
	int nelem, i, j, res;
	float matrix[3][3] = {{0,0,0}, {0,0,0}, {0,0,0}};

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "STR", &SIM, &hash_matrix, &div, &offset) == FAILURE) {
		RETURN_FALSE;
	}

	ZEND_FETCH_RESOURCE(im_src, gdImagePtr, &SIM, -1, "STR", le_gd);

	nelem = zend_hash_num_elements(Z_ARRVAL_P(hash_matrix));
	if (nelem != 3) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "STR");
		RETURN_FALSE;
	}

	for (i=0; i<3; i++) {
		if (zend_hash_index_find(Z_ARRVAL_P(hash_matrix), (i), (void **) &var) == SUCCESS && Z_TYPE_PP(var) == IS_ARRAY) {
			if (Z_TYPE_PP(var) != IS_ARRAY || zend_hash_num_elements(Z_ARRVAL_PP(var)) != 3 ) {
				php_error_docref(NULL TSRMLS_CC, E_WARNING, "STR");
				RETURN_FALSE;
			}

			for (j=0; j<3; j++) {
				if (zend_hash_index_find(Z_ARRVAL_PP(var), (j), (void **) &var2) == SUCCESS) {
					SEPARATE_ZVAL(var2);
					convert_to_double(*var2);
					matrix[i][j] = (float)Z_DVAL_PP(var2);
				} else {
					php_error_docref(NULL TSRMLS_CC, E_WARNING, "STR");
					RETURN_FALSE;
				}
			}
		}
	}
	res = gdImageConvolution(im_src, matrix, (float)div, (float)offset);

	if (res) {
		RETURN_TRUE;
	} else {
		RETURN_FALSE;
	}
}