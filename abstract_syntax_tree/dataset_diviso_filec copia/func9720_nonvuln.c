int smb_vfs_call_sys_acl_delete_def_file(struct vfs_handle_struct *handle,
					 const char *path)
{
	VFS_FIND(sys_acl_delete_def_file);
	return handle->fns->sys_acl_delete_def_file_fn(handle, path);
}