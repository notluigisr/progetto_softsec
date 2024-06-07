kvm_irqfd_release(struct kvm *kvm)
{
	struct kvm_kernel_irqfd *irqfd, *tmp;

	spin_lock_irq(&kvm->irqfds.lock);

	list_for_each_entry_safe(irqfd, tmp, &kvm->irqfds.items, list)
		irqfd_deactivate(irqfd);

	spin_unlock_irq(&kvm->irqfds.lock);

	
	flush_workqueue(irqfd_cleanup_wq);

}