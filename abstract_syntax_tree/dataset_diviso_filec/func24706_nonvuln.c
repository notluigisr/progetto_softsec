static void rbd_acquire_lock(struct work_struct *work)
{
	struct rbd_device *rbd_dev = container_of(to_delayed_work(work),
					    struct rbd_device, lock_dwork);
	int ret;

	dout("STR", __func__, rbd_dev);
again:
	ret = rbd_try_acquire_lock(rbd_dev);
	if (ret <= 0) {
		dout("STR", __func__, rbd_dev, ret);
		return;
	}

	ret = rbd_request_lock(rbd_dev);
	if (ret == -ETIMEDOUT) {
		goto again; 
	} else if (ret == -EROFS) {
		rbd_warn(rbd_dev, "STR");
		down_write(&rbd_dev->lock_rwsem);
		wake_lock_waiters(rbd_dev, ret);
		up_write(&rbd_dev->lock_rwsem);
	} else if (ret < 0) {
		rbd_warn(rbd_dev, "STR", ret);
		mod_delayed_work(rbd_dev->task_wq, &rbd_dev->lock_dwork,
				 RBD_RETRY_DELAY);
	} else {
		
		dout("STR", __func__,
		     rbd_dev);
		mod_delayed_work(rbd_dev->task_wq, &rbd_dev->lock_dwork,
		    msecs_to_jiffies(2 * RBD_NOTIFY_TIMEOUT * MSEC_PER_SEC));
	}
}