int sched_trace_rq_cpu(struct rq *rq)
{
	return rq ? cpu_of(rq) : -1;
}