struct kvm_vcpu *kvm_arch_vcpu_create(struct kvm *kvm,
						unsigned int id)
{
	if (check_tsc_unstable() && atomic_read(&kvm->online_vcpus) != 0)
		printk_once(KERN_WARNING
		"STR"
		"STR");
	return kvm_x86_ops->vcpu_create(kvm, id);
}