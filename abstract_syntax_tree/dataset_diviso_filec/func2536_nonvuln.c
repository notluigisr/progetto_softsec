static char * php_zipobj_get_filename(ze_zip_object *obj) 
{

	if (!obj) {
		return NULL;
	}

	if (obj->filename) {
		return obj->filename;
	}
	return NULL;
}