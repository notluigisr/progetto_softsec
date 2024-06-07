nautilus_file_recompute_deep_counts (NautilusFile *file)
{
	if (file->details->deep_counts_status != NAUTILUS_REQUEST_IN_PROGRESS) {
		file->details->deep_counts_status = NAUTILUS_REQUEST_NOT_STARTED;
		if (file->details->directory != NULL) {
			nautilus_directory_add_file_to_work_queue (file->details->directory, file);
			nautilus_directory_async_state_changed (file->details->directory);
		}
	}
}