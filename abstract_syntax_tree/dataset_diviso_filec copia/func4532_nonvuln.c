static void rbd_release_lock_work(struct work_struct *work)
{
	struct rbd_device *rbd_dev = container_of(work, struct rbd_device,
						  unlock_work);

	down_write(&rbd_dev->lock_rwsem);
	rbd_release_lock(rbd_dev);
	up_write(&rbd_dev->lock_rwsem);
}