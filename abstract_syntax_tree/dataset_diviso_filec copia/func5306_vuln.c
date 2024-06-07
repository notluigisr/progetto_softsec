static int coalesced_mmio_has_room(struct kvm_coalesced_mmio_dev *dev)
{
	struct kvm_coalesced_mmio_ring *ring;
	unsigned avail;

	

	
	ring = dev->kvm->coalesced_mmio_ring;
	avail = (ring->first - ring->last - 1) % KVM_COALESCED_MMIO_MAX;
	if (avail == 0) {
		
		return 0;
	}

	return 1;
}