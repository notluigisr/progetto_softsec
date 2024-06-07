int smb_vfs_call_sys_acl_create_entry(struct vfs_handle_struct *handle,
				      SMB_ACL_T *pacl, SMB_ACL_ENTRY_T *pentry)
{
	VFS_FIND(sys_acl_create_entry);
	return handle->fns->sys_acl_create_entry(handle, pacl, pentry);
}