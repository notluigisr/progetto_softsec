static int rbd_dev_refresh(struct rbd_device *rbd_dev)
{
	u64 mapping_size;
	int ret;

	down_write(&rbd_dev->header_rwsem);
	mapping_size = rbd_dev->mapping.size;

	ret = rbd_dev_header_info(rbd_dev);
	if (ret)
		goto out;

	
	if (rbd_dev->parent) {
		ret = rbd_dev_v2_parent_info(rbd_dev);
		if (ret)
			goto out;
	}

	rbd_assert(!rbd_is_snap(rbd_dev));
	rbd_dev->mapping.size = rbd_dev->header.image_size;

out:
	up_write(&rbd_dev->header_rwsem);
	if (!ret && mapping_size != rbd_dev->mapping.size)
		rbd_dev_update_size(rbd_dev);

	return ret;
}