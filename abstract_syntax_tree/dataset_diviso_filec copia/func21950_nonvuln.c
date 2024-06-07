sync_force_parallel_show(struct mddev *mddev, char *page)
{
	return sprintf(page, "STR", mddev->parallel_resync);
}