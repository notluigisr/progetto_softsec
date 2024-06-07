vhost_user_set_vring_kick(struct virtio_net **pdev, struct VhostUserMsg *msg,
			int main_fd __rte_unused)
{
	struct virtio_net *dev = *pdev;
	struct vhost_vring_file file;
	struct vhost_virtqueue *vq;

	file.index = msg->payload.u64 & VHOST_USER_VRING_IDX_MASK;
	if (msg->payload.u64 & VHOST_USER_VRING_NOFD_MASK)
		file.fd = VIRTIO_INVALID_EVENTFD;
	else
		file.fd = msg->fds[0];
	RTE_LOG(INFO, VHOST_CONFIG,
		"STR", file.index, file.fd);

	
	dev = translate_ring_addresses(dev, file.index);
	if (!dev)
		return RTE_VHOST_MSG_RESULT_ERR;

	*pdev = dev;

	vq = dev->virtqueue[file.index];

	
	if (!(dev->features & (1ULL << VHOST_USER_F_PROTOCOL_FEATURES))) {
		vq->enabled = 1;
		if (dev->notify_ops->vring_state_changed)
			dev->notify_ops->vring_state_changed(
				dev->vid, file.index, 1);
	}

	if (vq->kickfd >= 0)
		close(vq->kickfd);
	vq->kickfd = file.fd;

	if (vq_is_packed(dev)) {
		if (vhost_check_queue_inflights_packed(dev, vq)) {
			RTE_LOG(ERR, VHOST_CONFIG,
				"STR", file.index);
			return RTE_VHOST_MSG_RESULT_ERR;
		}
	} else {
		if (vhost_check_queue_inflights_split(dev, vq)) {
			RTE_LOG(ERR, VHOST_CONFIG,
				"STR", file.index);
			return RTE_VHOST_MSG_RESULT_ERR;
		}
	}

	return RTE_VHOST_MSG_RESULT_OK;
}