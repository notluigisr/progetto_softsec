nautilus_file_can_unmount (NautilusFile *file)
{
	g_return_val_if_fail (NAUTILUS_IS_FILE (file), FALSE);

	return file->details->can_unmount ||
		(file->details->mount != NULL &&
		 g_mount_can_unmount (file->details->mount));
}