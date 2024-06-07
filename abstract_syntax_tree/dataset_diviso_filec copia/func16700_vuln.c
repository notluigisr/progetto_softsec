static inline int object_custom(UNSERIALIZE_PARAMETER, zend_class_entry *ce)
{
	long datalen;

	datalen = parse_iv2((*p) + 2, p);

	(*p) += 2;

	if (datalen < 0 || (*p) + datalen >= max) {
		zend_error(E_WARNING, "STR", datalen, (long)(max - (*p)));
		return 0;
	}

	if (ce->unserialize == NULL) {
		zend_error(E_WARNING, "STR", ce->name);
		object_init_ex(*rval, ce);
	} else if (ce->unserialize(rval, ce, (const unsigned char*)*p, datalen, (zend_unserialize_data *)var_hash TSRMLS_CC) != SUCCESS) {
		return 0;
	}

	(*p) += datalen;

	return finish_nested_data(UNSERIALIZE_PASSTHRU);
}