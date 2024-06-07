#ifdef CONFIG_HAVE_KVM_PM_NOTIFIER
static int kvm_pm_notifier_call(struct notifier_block *bl,
				unsigned long state,
				void *unused)
{
	struct kvm *kvm = container_of(bl, struct kvm, pm_notifier);

	return kvm_arch_pm_notifier(kvm, state);