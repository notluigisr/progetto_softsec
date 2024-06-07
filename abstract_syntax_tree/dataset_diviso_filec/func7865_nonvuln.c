static int adouble_destructor(struct adouble *ad)
{
	NTSTATUS status;

	if (!ad->ad_opened) {
		return 0;
	}

	SMB_ASSERT(ad->ad_fsp != NULL);

	status = fd_close(ad->ad_fsp);
	if (!NT_STATUS_IS_OK(status)) {
		DBG_ERR("STR",
			fsp_str_dbg(ad->ad_fsp), nt_errstr(status));
	}
	file_free(NULL, ad->ad_fsp);
	ad->ad_fsp = NULL;
	ad->ad_opened = false;

	return 0;
}