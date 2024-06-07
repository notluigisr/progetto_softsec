ssize_t smb_vfs_call_listxattr(struct vfs_handle_struct *handle,
			       const char *path, char *list, size_t size)
{
	VFS_FIND(listxattr);
	return handle->fns->listxattr(handle, path, list, size);
}