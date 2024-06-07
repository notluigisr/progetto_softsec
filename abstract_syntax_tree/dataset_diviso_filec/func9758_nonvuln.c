static __inline__ void ax25_cb_put(ax25_cb *ax25)
{
	if (refcount_dec_and_test(&ax25->refcount)) {
		kfree(ax25->digipeat);
		kfree(ax25);
	}
}