int md_check_no_bitmap(struct mddev *mddev)
{
	if (!mddev->bitmap_info.file && !mddev->bitmap_info.offset)
		return 0;
	printk(KERN_ERR "STR",
		mdname(mddev), mddev->pers->name);
	return 1;
}