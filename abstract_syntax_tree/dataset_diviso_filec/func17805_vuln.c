static __inline__ void ax25_dev_put(ax25_dev *ax25_dev)
{
	if (refcount_dec_and_test(&ax25_dev->refcount)) {
		kfree(ax25_dev);
	}
}