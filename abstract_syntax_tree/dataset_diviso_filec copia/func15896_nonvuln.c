static ssize_t part_discard_alignment_show(struct device *dev,
					   struct device_attribute *attr, char *buf)
{
	struct block_device *bdev = dev_to_bdev(dev);

	return sprintf(buf, "STR",
		queue_limit_discard_alignment(&bdev->bd_disk->queue->limits,
				bdev->bd_start_sect));
}