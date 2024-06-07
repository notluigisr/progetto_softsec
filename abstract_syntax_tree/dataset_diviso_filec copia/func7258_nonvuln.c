static int vhost_iotlb_miss(struct vhost_virtqueue *vq, u64 iova, int access)
{
	struct vhost_dev *dev = vq->dev;
	struct vhost_msg_node *node;
	struct vhost_iotlb_msg *msg;
	bool v2 = vhost_backend_has_feature(vq, VHOST_BACKEND_F_IOTLB_MSG_V2);

	node = vhost_new_msg(vq, v2 ? VHOST_IOTLB_MSG_V2 : VHOST_IOTLB_MSG);
	if (!node)
		return -ENOMEM;

	if (v2) {
		node->msg_v2.type = VHOST_IOTLB_MSG_V2;
		msg = &node->msg_v2.iotlb;
	} else {
		msg = &node->msg.iotlb;
	}

	msg->type = VHOST_IOTLB_MISS;
	msg->iova = iova;
	msg->perm = access;

	vhost_enqueue_msg(dev, &dev->read_list, node);

	return 0;
}