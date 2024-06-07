vhost_user_set_vring_base(struct virtio_net **pdev,
			struct VhostUserMsg *msg,
			int main_fd __rte_unused)
{
	struct virtio_net *dev = *pdev;
	struct vhost_virtqueue *vq = dev->virtqueue[msg->payload.state.index];
	uint64_t val = msg->payload.state.num;

	if (vq_is_packed(dev)) {
		
		vq->last_avail_idx = val & 0x7fff;
		vq->avail_wrap_counter = !!(val & (0x1 << 15));
		
		vq->last_used_idx = vq->last_avail_idx;
		vq->used_wrap_counter = vq->avail_wrap_counter;
	} else {
		vq->last_used_idx = msg->payload.state.num;
		vq->last_avail_idx = msg->payload.state.num;
	}

	return RTE_VHOST_MSG_RESULT_OK;
}