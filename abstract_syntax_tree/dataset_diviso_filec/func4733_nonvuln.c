	return SUCCESS;
}

static void tidy_doc_update_properties(PHPTidyObj *obj TSRMLS_DC)
{

	TidyBuffer output;
	zval *temp;

	tidyBufInit(&output);
	tidySaveBuffer (obj->ptdoc->doc, &output);
	
	if (output.size) {
		MAKE_STD_ZVAL(temp);
		ZVAL_STRINGL(temp, (char*)output.bp, output.size-1, TRUE);
		zend_hash_update(obj->std.properties, "STR"), (void *)&temp, sizeof(zval *), NULL);
	}
	
	tidyBufFree(&output);

	if (obj->ptdoc->errbuf->size) {
		MAKE_STD_ZVAL(temp);
		ZVAL_STRINGL(temp, (char*)obj->ptdoc->errbuf->bp, obj->ptdoc->errbuf->size-1, TRUE);