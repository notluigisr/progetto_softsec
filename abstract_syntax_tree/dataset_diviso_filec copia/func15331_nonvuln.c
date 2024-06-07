static void rbd_notify_released_lock(struct work_struct *work)
{
	struct rbd_device *rbd_dev = container_of(work, struct rbd_device,
						  released_lock_work);

	rbd_notify_op_lock(rbd_dev, RBD_NOTIFY_OP_RELEASED_LOCK);
}