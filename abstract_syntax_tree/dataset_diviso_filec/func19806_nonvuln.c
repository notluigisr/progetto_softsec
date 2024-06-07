ssize_t vhost_chr_write_iter(struct vhost_dev *dev,
			     struct iov_iter *from)
{
	struct vhost_iotlb_msg msg;
	size_t offset;
	int type, ret;

	ret = copy_from_iter(&type, sizeof(type), from);
	if (ret != sizeof(type)) {
		ret = -EINVAL;
		goto done;
	}

	switch (type) {
	case VHOST_IOTLB_MSG:
		
		offset = offsetof(struct vhost_msg, iotlb) - sizeof(int);
		break;
	case VHOST_IOTLB_MSG_V2:
		offset = sizeof(__u32);
		break;
	default:
		ret = -EINVAL;
		goto done;
	}

	iov_iter_advance(from, offset);
	ret = copy_from_iter(&msg, sizeof(msg), from);
	if (ret != sizeof(msg)) {
		ret = -EINVAL;
		goto done;
	}
	if (vhost_process_iotlb_msg(dev, &msg)) {
		ret = -EFAULT;
		goto done;
	}

	ret = (type == VHOST_IOTLB_MSG) ? sizeof(struct vhost_msg) :
	      sizeof(struct vhost_msg_v2);
done:
	return ret;
}