static void lcb_put(struct lcb *lcb)
{
	if (lcb->alloc)
		kfree(lcb->log_rec);
	kfree(lcb->lrh);
	kfree(lcb);
}