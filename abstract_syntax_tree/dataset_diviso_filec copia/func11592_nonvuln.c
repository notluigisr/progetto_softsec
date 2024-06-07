ssize_t smb_vfs_call_pwrite(struct vfs_handle_struct *handle,
			    struct files_struct *fsp, const void *data,
			    size_t n, off_t offset)
{
	VFS_FIND(pwrite);
	return handle->fns->pwrite_fn(handle, fsp, data, n, offset);
}