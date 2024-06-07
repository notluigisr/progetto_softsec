abort_job (CommonJob *job)
{
	g_cancellable_cancel (job->cancellable);
	
}