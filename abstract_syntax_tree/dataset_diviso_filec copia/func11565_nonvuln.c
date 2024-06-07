directory_count_stop (NautilusDirectory *directory)
{
	NautilusFile *file;

	if (directory->details->count_in_progress != NULL) {
		file = directory->details->count_in_progress->count_file;
		if (file != NULL) {
			g_assert (NAUTILUS_IS_FILE (file));
			g_assert (file->details->directory == directory);
			if (is_needy (file,
				      should_get_directory_count_now,
				      REQUEST_DIRECTORY_COUNT)) {
				return;
			}
		}

		
		directory_count_cancel (directory);
	}
}