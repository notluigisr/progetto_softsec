void gf_filter_post_process_task_internal(GF_Filter *filter, Bool use_direct_dispatch)
{
	if (filter->finalized || filter->removed)
		return;

	
#if 0
	
	
	if (!use_direct_dispatch && filter->in_process_callback) {
		filter->schedule_next_time = 1 + gf_sys_clock_high_res();
		return;
	}
#endif

	
	gf_mx_p(filter->tasks_mx);
	assert((s32)filter->process_task_queued>=0);

	if (use_direct_dispatch) {
		safe_int_inc(&filter->process_task_queued);
		gf_fs_post_task_ex(filter->session, gf_filter_process_task, filter, NULL, "STR", NULL, GF_FALSE, GF_TRUE);
	} else if (safe_int_inc(&filter->process_task_queued) <= 1) {
		GF_LOG(GF_LOG_DEBUG, GF_LOG_FILTER, ("STR", filter->freg->name));
		gf_fs_post_task(filter->session, gf_filter_process_task, filter, NULL, "STR", NULL);
	} else {
		GF_LOG(GF_LOG_DEBUG, GF_LOG_FILTER, ("STR", filter->freg->name));
		assert(filter->session->run_status
		 		|| filter->session->in_final_flush
		 		|| filter->disabled
				|| filter->scheduled_for_next_task
				|| filter->session->direct_mode
		 		|| gf_fq_count(filter->tasks)
		);
	}
	if (!filter->session->direct_mode && !use_direct_dispatch) {
		assert(filter->process_task_queued);
	}
	gf_mx_v(filter->tasks_mx);
}