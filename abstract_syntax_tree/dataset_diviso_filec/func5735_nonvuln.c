int jbd2_journal_start_reserved(handle_t *handle, unsigned int type,
				unsigned int line_no)
{
	journal_t *journal = handle->h_journal;
	int ret = -EIO;

	if (WARN_ON(!handle->h_reserved)) {
		
		jbd2_journal_stop(handle);
		return ret;
	}
	
	if (WARN_ON(current->journal_info)) {
		jbd2_journal_free_reserved(handle);
		return ret;
	}

	handle->h_journal = NULL;
	
	ret = start_this_handle(journal, handle, GFP_NOFS);
	if (ret < 0) {
		handle->h_journal = journal;
		jbd2_journal_free_reserved(handle);
		return ret;
	}
	handle->h_type = type;
	handle->h_line_no = line_no;
	return 0;
}