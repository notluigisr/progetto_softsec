	__must_hold(wqe->lock)
{
	struct io_wqe_acct *acct = &wqe->acct[index];

	
	if (!hlist_nulls_empty(&wqe->free_list) || !io_wqe_run_queue(wqe))
		return false;
	return acct->nr_workers < acct->max_workers;
}