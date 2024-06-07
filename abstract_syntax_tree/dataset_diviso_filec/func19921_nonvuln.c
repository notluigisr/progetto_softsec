rename_data_new (const char *path_to_rename,
		 const char *old_name,
		 const char *new_name,
		 const char *current_dir,
		 gboolean    is_dir,
		 gboolean    dir_in_archive,
		 const char *original_path)
{
	RenameData *rdata;

	rdata = g_new0 (RenameData, 1);
	rdata->path_to_rename = g_strdup (path_to_rename);
	if (old_name != NULL)
		rdata->old_name = g_strdup (old_name);
	if (new_name != NULL)
		rdata->new_name = g_strdup (new_name);
	if (current_dir != NULL)
		rdata->current_dir = g_strdup (current_dir);
	rdata->is_dir = is_dir;
	rdata->dir_in_archive = dir_in_archive;
	if (original_path != NULL)
		rdata->original_path = g_strdup (original_path);

	return rdata;
}