static void blk_exit_queue(struct request_queue *q)
{
	
	if (q->elevator) {
		ioc_clear_queue(q);
		elevator_exit(q, q->elevator);
		q->elevator = NULL;
	}

	
	blkcg_exit_queue(q);

	
	bdi_put(q->backing_dev_info);
}