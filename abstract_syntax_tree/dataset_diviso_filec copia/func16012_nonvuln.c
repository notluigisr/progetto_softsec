void smb_vfs_call_init_search_op(struct vfs_handle_struct *handle,
				 DIR *dirp)
{
	VFS_FIND(init_search_op);
	handle->fns->init_search_op_fn(handle, dirp);
}