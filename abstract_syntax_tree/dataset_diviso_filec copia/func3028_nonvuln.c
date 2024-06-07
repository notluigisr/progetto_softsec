int smb_vfs_call_chmod_acl(struct vfs_handle_struct *handle, const char *name,
			   mode_t mode)
{
	VFS_FIND(chmod_acl);
	return handle->fns->chmod_acl_fn(handle, name, mode);
}