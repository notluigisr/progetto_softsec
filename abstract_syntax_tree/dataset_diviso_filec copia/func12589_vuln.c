void blk_cleanup_queue(struct request_queue *q)
{
	
	mutex_lock(&q->sysfs_lock);
	blk_set_queue_dying(q);

	blk_queue_flag_set(QUEUE_FLAG_NOMERGES, q);
	blk_queue_flag_set(QUEUE_FLAG_NOXMERGES, q);
	blk_queue_flag_set(QUEUE_FLAG_DYING, q);
	mutex_unlock(&q->sysfs_lock);

	
	blk_freeze_queue(q);

	rq_qos_exit(q);

	blk_queue_flag_set(QUEUE_FLAG_DEAD, q);

	
	blk_flush_integrity();

	
	del_timer_sync(&q->backing_dev_info->laptop_mode_wb_timer);
	blk_sync_queue(q);

	if (queue_is_mq(q))
		blk_mq_exit_queue(q);

	percpu_ref_exit(&q->q_usage_counter);

	
	blk_put_queue(q);
}