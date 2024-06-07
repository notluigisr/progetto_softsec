static void schedule_defer_open(struct share_mode_lock *lck,
				struct file_id id,
				struct timeval request_time,
				struct smb_request *req)
{
	struct deferred_open_record state;

	

	struct timeval timeout;

	

	timeout = timeval_set(OPLOCK_BREAK_TIMEOUT*2, 0);

	

	state.delayed_for_oplocks = True;
	state.async_open = false;
	state.id = id;

	if (!request_timed_out(request_time, timeout)) {
		defer_open(lck, request_time, timeout, req, &state);
	}
}