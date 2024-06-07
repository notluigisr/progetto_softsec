static int set_sec_attr(sc_file_t *file, unsigned int am, unsigned int ac, 
	unsigned int meth)
{
	const amode_entry_t *table;

        
	if (meth == SC_AC_CHV && ac == 0)
		meth = SC_AC_AUT;

	if (file->type == SC_FILE_TYPE_DF)
		table = df_amode_table;
	else if (file->type == SC_FILE_TYPE_WORKING_EF)
		table = wef_amode_table;
	else if (file->type == SC_FILE_TYPE_INTERNAL_EF)
		table = ief_amode_table;
	else
		return SC_ERROR_INVALID_ARGUMENTS;
	for (; table->am != 0; table++) {
		if (table->am & am)
			sc_file_add_acl_entry(file, table->sc, meth, ac);
	}
	return SC_SUCCESS;
}