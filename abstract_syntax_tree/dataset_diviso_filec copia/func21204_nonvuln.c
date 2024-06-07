_zip_set_open_error(int *zep, const zip_error_t *err, int ze)
{
    if (err) {
	ze = zip_error_code_zip(err);
	if (zip_error_system_type(err) == ZIP_ET_SYS) {
	    errno = zip_error_code_system(err);
	}
    }

    if (zep)
	*zep = ze;
}