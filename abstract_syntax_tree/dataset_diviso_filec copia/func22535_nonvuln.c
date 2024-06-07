worker_err_ratelimit(struct worker* worker, int err)
{
	if(worker->err_limit_time == *worker->env.now) {
		
		if(worker->err_limit_count++ > ERROR_RATELIMIT)
			return -1;
	} else {
		
		worker->err_limit_time = *worker->env.now;
		worker->err_limit_count = 1;
	}
	return err;
}