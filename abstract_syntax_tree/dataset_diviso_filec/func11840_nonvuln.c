static void mld_report_stop_work(struct inet6_dev *idev)
{
	if (cancel_delayed_work_sync(&idev->mc_report_work))
		__in6_dev_put(idev);
}