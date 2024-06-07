deep_count_callback (GObject *source_object,
		     GAsyncResult *res,
		     gpointer user_data)
{
	DeepCountState *state;
	GFileEnumerator *enumerator;
	NautilusFile *file;

	state = user_data;

	if (state->directory == NULL) {
		
		deep_count_state_free (state);
		return;
	}

	file = state->directory->details->deep_count_file;

	enumerator = g_file_enumerate_children_finish  (G_FILE (source_object),	res, NULL);
	
	if (enumerator == NULL) {
		file->details->deep_unreadable_count += 1;
		
		deep_count_next_dir (state);
	} else {
		state->enumerator = enumerator;
		g_file_enumerator_next_files_async (state->enumerator,
						    DIRECTORY_LOAD_ITEMS_PER_CALLBACK,
						    G_PRIORITY_LOW,
						    state->cancellable,
						    deep_count_more_files_callback,
						    state);
	}
}