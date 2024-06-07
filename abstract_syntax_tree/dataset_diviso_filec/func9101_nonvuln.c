sync_completed_show(struct mddev *mddev, char *page)
{
	unsigned long long max_sectors, resync;

	if (!test_bit(MD_RECOVERY_RUNNING, &mddev->recovery))
		return sprintf(page, "STR");

	if (mddev->curr_resync == 1 ||
	    mddev->curr_resync == 2)
		return sprintf(page, "STR");

	if (test_bit(MD_RECOVERY_SYNC, &mddev->recovery) ||
	    test_bit(MD_RECOVERY_RESHAPE, &mddev->recovery))
		max_sectors = mddev->resync_max_sectors;
	else
		max_sectors = mddev->dev_sectors;

	resync = mddev->curr_resync_completed;
	return sprintf(page, "STR", resync, max_sectors);
}