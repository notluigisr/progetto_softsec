nautilus_file_can_get_owner (NautilusFile *file)
{
	
	return file->details->uid != -1;
}