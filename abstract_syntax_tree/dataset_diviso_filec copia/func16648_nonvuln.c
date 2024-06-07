bool smb_vfs_call_aio_force(struct vfs_handle_struct *handle,
			    struct files_struct *fsp)
{
	VFS_FIND(aio_force);
	return handle->fns->aio_force(handle, fsp);
}