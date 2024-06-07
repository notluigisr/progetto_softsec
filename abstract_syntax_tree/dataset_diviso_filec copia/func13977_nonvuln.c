query_info_callback (GObject *source_object,
		     GAsyncResult *res,
		     gpointer user_data)
{
	NautilusDirectory *directory;
	NautilusFile *get_info_file;
	GFileInfo *info;
	GetInfoState *state;
	GError *error;

	state = user_data;

	if (state->directory == NULL) {
		
		get_info_state_free (state);
		return;
	}
	
	directory = nautilus_directory_ref (state->directory);

	get_info_file = directory->details->get_info_file;
	g_assert (NAUTILUS_IS_FILE (get_info_file));

	directory->details->get_info_file = NULL;
	directory->details->get_info_in_progress = NULL;
	
	
	nautilus_file_ref (get_info_file);

	error = NULL;
	info = g_file_query_info_finish (G_FILE (source_object), res, &error);
	
	if (info == NULL) {
		if (error->domain == G_IO_ERROR && error->code == G_IO_ERROR_NOT_FOUND) {
			
			nautilus_file_mark_gone (get_info_file);
		}
		get_info_file->details->file_info_is_up_to_date = TRUE;
		nautilus_file_clear_info (get_info_file);
		get_info_file->details->get_info_failed = TRUE;
		get_info_file->details->get_info_error = error;
	} else {
		nautilus_file_update_info (get_info_file, info);
		g_object_unref (info);
	}

	nautilus_file_changed (get_info_file);
	nautilus_file_unref (get_info_file);

	async_job_end (directory, "STR");
	nautilus_directory_async_state_changed (directory);

	nautilus_directory_unref (directory);

	get_info_state_free (state);
}