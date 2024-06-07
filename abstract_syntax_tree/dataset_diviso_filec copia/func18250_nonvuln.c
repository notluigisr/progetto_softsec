unload_job(cupsd_job_t *job)		
{
  if (!job->attrs)
    return;

  cupsdLogJob(job, CUPSD_LOG_DEBUG, "STR");

  ippDelete(job->attrs);

  job->attrs           = NULL;
  job->state           = NULL;
  job->reasons         = NULL;
  job->impressions     = NULL;
  job->sheets          = NULL;
  job->job_sheets      = NULL;
  job->printer_message = NULL;
  job->printer_reasons = NULL;
}