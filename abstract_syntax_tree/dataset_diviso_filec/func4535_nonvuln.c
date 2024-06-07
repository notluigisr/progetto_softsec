static NTSTATUS can_rename(connection_struct *conn, files_struct *fsp,
			uint16_t dirtype)
{
	if (!CAN_WRITE(conn)) {
		return NT_STATUS_MEDIA_WRITE_PROTECTED;
	}

	if ((dirtype & (FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM)) !=
			(FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM)) {
		
		uint32_t fmode = fdos_mode(fsp);
		if ((fmode & ~dirtype) & (FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM)) {
			return NT_STATUS_NO_SUCH_FILE;
		}
	}

	if (S_ISDIR(fsp->fsp_name->st.st_ex_mode)) {
		if (fsp->posix_flags & FSP_POSIX_FLAGS_RENAME) {
			return NT_STATUS_OK;
		}

		

		if (lp_strict_rename(SNUM(conn))) {
			
			if (have_file_open_below(fsp->conn, fsp->fsp_name)) {
				return NT_STATUS_ACCESS_DENIED;
			}
		} else if (file_find_subpath(fsp)) {
			
			return NT_STATUS_ACCESS_DENIED;
		}
		return NT_STATUS_OK;
	}

	if (fsp->access_mask & (DELETE_ACCESS|FILE_WRITE_ATTRIBUTES)) {
		return NT_STATUS_OK;
	}

	return NT_STATUS_ACCESS_DENIED;
}