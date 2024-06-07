mark_trusted_job_done (gpointer user_data)
{
	MarkTrustedJob *job = user_data;
	
	g_object_unref (job->file);

	if (job->done_callback) {
		job->done_callback (job->done_callback_data);
	}
	
	finalize_common ((CommonJob *)job);
	return FALSE;
}