add_cfs_task_weight(struct cfs_rq *cfs_rq, unsigned long weight)
{
	cfs_rq->task_weight += weight;
}