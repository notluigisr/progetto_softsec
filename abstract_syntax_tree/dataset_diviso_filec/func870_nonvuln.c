static int dio_bio_end_aio(struct bio *bio, unsigned int bytes_done, int error)
{
	struct dio *dio = bio->bi_private;
	unsigned long remaining;
	unsigned long flags;

	if (bio->bi_size)
		return 1;

	
	dio_bio_complete(dio, bio);

	spin_lock_irqsave(&dio->bio_lock, flags);
	remaining = --dio->refcount;
	if (remaining == 1 && dio->waiter)
		wake_up_process(dio->waiter);
	spin_unlock_irqrestore(&dio->bio_lock, flags);

	if (remaining == 0) {
		int ret = dio_complete(dio, dio->iocb->ki_pos, 0);
		aio_complete(dio->iocb, ret, 0);
		kfree(dio);
	}

	return 0;
}