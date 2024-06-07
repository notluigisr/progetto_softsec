NTSTATUS smb_vfs_call_snap_delete(struct vfs_handle_struct *handle,
				  TALLOC_CTX *mem_ctx,
				  char *base_path,
				  char *snap_path)
{
	VFS_FIND(snap_delete);
	return handle->fns->snap_delete_fn(handle, mem_ctx, base_path,
					   snap_path);
}