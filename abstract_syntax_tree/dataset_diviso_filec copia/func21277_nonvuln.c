static void fsl_hv_queue_doorbell(uint32_t doorbell)
{
	struct doorbell_queue *dbq;
	unsigned long flags;

	
	spin_lock_irqsave(&db_list_lock, flags);

	list_for_each_entry(dbq, &db_list, list) {
		if (dbq->head != nextp(dbq->tail)) {
			dbq->q[dbq->tail] = doorbell;
			
			smp_wmb();
			dbq->tail = nextp(dbq->tail);
			wake_up_interruptible(&dbq->wait);
		}
	}

	spin_unlock_irqrestore(&db_list_lock, flags);
}