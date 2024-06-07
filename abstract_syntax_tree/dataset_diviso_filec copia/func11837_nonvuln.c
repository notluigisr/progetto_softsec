bool smbd_dirptr_lanman2_entry(TALLOC_CTX *ctx,
			       connection_struct *conn,
			       struct dptr_struct *dirptr,
			       uint16 flags2,
			       const char *path_mask,
			       uint32 dirtype,
			       int info_level,
			       int requires_resume_key,
			       bool dont_descend,
			       bool ask_sharemode,
			       uint8_t align,
			       bool do_pad,
			       char **ppdata,
			       char *base_data,
			       char *end_data,
			       int space_remaining,
			       bool *out_of_space,
			       bool *got_exact_match,
			       int *_last_entry_off,
			       struct ea_list *name_list)
{
	const char *p;
	const char *mask = NULL;
	long prev_dirpos = 0;
	uint32_t mode = 0;
	char *fname = NULL;
	struct smb_filename *smb_fname = NULL;
	struct smbd_dirptr_lanman2_state state;
	bool ok;
	uint64_t last_entry_off = 0;

	ZERO_STRUCT(state);
	state.conn = conn;
	state.info_level = info_level;
	state.check_mangled_names = lp_manglednames(conn->params);
	state.has_wild = dptr_has_wild(dirptr);
	state.got_exact_match = false;

	*out_of_space = false;
	*got_exact_match = false;

	p = strrchr_m(path_mask,'/');
	if(p != NULL) {
		if(p[1] == '\0') {
			mask = "STR";
		} else {
			mask = p+1;
		}
	} else {
		mask = path_mask;
	}

	ok = smbd_dirptr_get_entry(ctx,
				   dirptr,
				   mask,
				   dirtype,
				   dont_descend,
				   ask_sharemode,
				   smbd_dirptr_lanman2_match_fn,
				   smbd_dirptr_lanman2_mode_fn,
				   &state,
				   &fname,
				   &smb_fname,
				   &mode,
				   &prev_dirpos);
	if (!ok) {
		return false;
	}

	*got_exact_match = state.got_exact_match;

	ok = smbd_marshall_dir_entry(ctx,
				     conn,
				     flags2,
				     info_level,
				     name_list,
				     state.check_mangled_names,
				     requires_resume_key,
				     mode,
				     fname,
				     smb_fname,
				     space_remaining,
				     align,
				     do_pad,
				     base_data,
				     ppdata,
				     end_data,
				     out_of_space,
				     &last_entry_off);
	TALLOC_FREE(fname);
	TALLOC_FREE(smb_fname);
	if (*out_of_space) {
		dptr_SeekDir(dirptr, prev_dirpos);
		return false;
	}
	if (!ok) {
		return false;
	}

	*_last_entry_off = last_entry_off;
	return true;
}