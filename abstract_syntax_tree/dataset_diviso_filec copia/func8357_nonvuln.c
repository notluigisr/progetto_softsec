static int vfswrap_ftruncate(vfs_handle_struct *handle, files_struct *fsp, off_t len)
{
	int result = -1;
	SMB_STRUCT_STAT *pst;
	NTSTATUS status;
	char c = 0;

	START_PROFILE(syscall_ftruncate);

	if (lp_strict_allocate(SNUM(fsp->conn)) && !fsp->is_sparse) {
		result = strict_allocate_ftruncate(handle, fsp, len);
		END_PROFILE(syscall_ftruncate);
		return result;
	}

	

	result = ftruncate(fsp->fh->fd, len);
	if (result == 0)
		goto done;

	

	
	status = vfs_stat_fsp(fsp);
	if (!NT_STATUS_IS_OK(status)) {
		goto done;
	}
	pst = &fsp->fsp_name->st;

#ifdef S_ISFIFO
	if (S_ISFIFO(pst->st_ex_mode)) {
		result = 0;
		goto done;
	}
#endif

	if (pst->st_ex_size == len) {
		result = 0;
		goto done;
	}

	if (pst->st_ex_size > len) {
		
		goto done;
	}

	if (SMB_VFS_PWRITE(fsp, &c, 1, len-1)!=1) {
		goto done;
	}

	result = 0;

  done:

	END_PROFILE(syscall_ftruncate);
	return result;
}