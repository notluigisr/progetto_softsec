set_file_unconfirmed (NautilusFile *file, gboolean unconfirmed)
{
	NautilusDirectory *directory;

	g_assert (NAUTILUS_IS_FILE (file));
	g_assert (unconfirmed == FALSE || unconfirmed == TRUE);

	if (file->details->unconfirmed == unconfirmed) {
		return;
	}
	file->details->unconfirmed = unconfirmed;

	directory = file->details->directory;
	if (unconfirmed) {
		directory->details->confirmed_file_count--;
	} else {
		directory->details->confirmed_file_count++;
	}
}