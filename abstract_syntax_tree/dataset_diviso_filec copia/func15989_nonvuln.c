NTSTATUS smb_vfs_call_readdir_attr(struct vfs_handle_struct *handle,
				   const struct smb_filename *fname,
				   TALLOC_CTX *mem_ctx,
				   struct readdir_attr_data **attr_data)
{
	VFS_FIND(readdir_attr);
	return handle->fns->readdir_attr_fn(handle, fname, mem_ctx, attr_data);
}