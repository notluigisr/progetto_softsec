nautilus_file_get_date (NautilusFile *file,
			NautilusDateType date_type,
			time_t *date)
{
	if (date != NULL) {
		*date = 0;
	}

	g_return_val_if_fail (date_type == NAUTILUS_DATE_TYPE_CHANGED
			      || date_type == NAUTILUS_DATE_TYPE_ACCESSED
			      || date_type == NAUTILUS_DATE_TYPE_MODIFIED
			      || date_type == NAUTILUS_DATE_TYPE_PERMISSIONS_CHANGED, FALSE);

	if (file == NULL) {
		return FALSE;
	}

	g_return_val_if_fail (NAUTILUS_IS_FILE (file), FALSE);

	return EEL_CALL_METHOD_WITH_RETURN_VALUE
		(NAUTILUS_FILE_CLASS, file,
		 get_date, (file, date_type, date));
}