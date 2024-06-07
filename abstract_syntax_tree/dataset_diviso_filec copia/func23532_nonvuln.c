bool vhost_vq_avail_empty(struct vhost_dev *dev, struct vhost_virtqueue *vq)
{
	__virtio16 avail_idx;
	int r;

	if (vq->avail_idx != vq->last_avail_idx)
		return false;

	r = vhost_get_avail_idx(vq, &avail_idx);
	if (unlikely(r))
		return false;
	vq->avail_idx = vhost16_to_cpu(vq, avail_idx);

	return vq->avail_idx == vq->last_avail_idx;
}