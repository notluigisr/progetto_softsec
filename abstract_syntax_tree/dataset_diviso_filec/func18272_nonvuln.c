invalidate_mime_list (NautilusFile *file)
{
	file->details->mime_list_is_up_to_date = FALSE;
}