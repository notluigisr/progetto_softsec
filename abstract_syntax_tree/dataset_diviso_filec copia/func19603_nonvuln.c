
static void kvm_resume(void)
{
	if (kvm_usage_count) {
		lockdep_assert_not_held(&kvm_count_lock);
		hardware_enable_nolock(NULL);
	}