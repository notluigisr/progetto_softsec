static void rbd_dev_destroy(struct rbd_device *rbd_dev)
{
	if (rbd_dev)
		put_device(&rbd_dev->dev);
}