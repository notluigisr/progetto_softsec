nautilus_file_is_home (NautilusFile *file)
{
	GFile *dir;

	dir = file->details->directory->details->location;
	if (dir == NULL) {
		return FALSE;
	}

	return nautilus_is_home_directory_file (dir,
						eel_ref_str_peek (file->details->name));
}