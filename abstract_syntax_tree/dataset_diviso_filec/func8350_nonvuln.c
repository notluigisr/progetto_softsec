size_t srvstr_get_path(TALLOC_CTX *ctx,
			const char *base_ptr,
			uint16_t smb_flags2,
			char **pp_dest,
			const char *src,
			size_t src_len,
			int flags,
			NTSTATUS *err)
{
	return srvstr_get_path_internal(ctx,
			base_ptr,
			smb_flags2,
			pp_dest,
			src,
			src_len,
			flags,
			false,
			err);
}