vq_endchains(struct virtio_vq_info *vq, int used_all_avail)
{
	struct virtio_base *base;
	uint16_t event_idx, new_idx, old_idx;
	int intr;

	

	atomic_thread_fence();

	base = vq->base;
	old_idx = vq->save_used;
	vq->save_used = new_idx = vq->used->idx;
	if (used_all_avail &&
	    (base->negotiated_caps & (1 << VIRTIO_F_NOTIFY_ON_EMPTY)))
		intr = 1;
	else if (base->negotiated_caps & (1 << VIRTIO_RING_F_EVENT_IDX)) {
		event_idx = VQ_USED_EVENT_IDX(vq);
		
		intr = (uint16_t)(new_idx - event_idx - 1) <
			(uint16_t)(new_idx - old_idx);
	} else {
		intr = new_idx != old_idx &&
		    !(vq->avail->flags & VRING_AVAIL_F_NO_INTERRUPT);
	}
	if (intr)
		vq_interrupt(base, vq);
}