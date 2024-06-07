compare_completed_jobs(void *first,	
                       void *second,	
		       void *data)	
{
  int	diff;				


  (void)data;

  if ((diff = ((cupsd_job_t *)second)->completed_time -
              ((cupsd_job_t *)first)->completed_time) != 0)
    return (diff);
  else
    return (((cupsd_job_t *)first)->id - ((cupsd_job_t *)second)->id);
}