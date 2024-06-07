int jbd2__journal_restart(handle_t *handle, int nblocks, int revoke_records,
			  gfp_t gfp_mask)
{
	transaction_t *transaction = handle->h_transaction;
	journal_t *journal;
	tid_t		tid;
	int		need_to_start;
	int		ret;

	
	if (is_handle_aborted(handle))
		return 0;
	journal = transaction->t_journal;
	tid = transaction->t_tid;

	
	jbd_debug(2, "STR", handle);
	stop_this_handle(handle);
	handle->h_transaction = NULL;

	
	read_lock(&journal->j_state_lock);
	need_to_start = !tid_geq(journal->j_commit_request, tid);
	read_unlock(&journal->j_state_lock);
	if (need_to_start)
		jbd2_log_start_commit(journal, tid);
	handle->h_total_credits = nblocks +
		DIV_ROUND_UP(revoke_records,
			     journal->j_revoke_records_per_block);
	handle->h_revoke_credits = revoke_records;
	ret = start_this_handle(journal, handle, gfp_mask);
	trace_jbd2_handle_restart(journal->j_fs_dev->bd_dev,
				 ret ? 0 : handle->h_transaction->t_tid,
				 handle->h_type, handle->h_line_no,
				 handle->h_total_credits);
	return ret;
}