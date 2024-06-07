struct adouble *ad_get(TALLOC_CTX *ctx,
			      vfs_handle_struct *handle,
			      const struct smb_filename *smb_fname,
			      adouble_type_t type)
{
	return ad_get_internal(ctx, handle, NULL, smb_fname, type);
}