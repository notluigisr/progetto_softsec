suspend_job (GSWindow  *window,
             GSJob     *job,
             GSManager *manager)
{
        gs_job_suspend (job, TRUE);
}