e_ews_attachment_info_get_filename (EEwsAttachmentInfo *info)
{
	g_return_val_if_fail (info != NULL, NULL);
	g_return_val_if_fail (info->type == E_EWS_ATTACHMENT_INFO_TYPE_INLINED, NULL);

	return info->data.inlined.filename;
}