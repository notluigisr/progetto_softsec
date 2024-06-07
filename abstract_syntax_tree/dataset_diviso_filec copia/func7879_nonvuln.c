nautilus_file_update_info (NautilusFile *file,
			   GFileInfo *info)
{
	return update_info_internal (file, info, FALSE);
}