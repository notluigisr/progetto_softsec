static void kvm_write_wall_clock(struct kvm *kvm, gpa_t wall_clock)
{
	static int version;
	struct pvclock_wall_clock wc;
	struct timespec now, sys, boot;

	if (!wall_clock)
		return;

	version++;

	kvm_write_guest(kvm, wall_clock, &version, sizeof(version));

	
	now = current_kernel_time();
	ktime_get_ts(&sys);
	boot = ns_to_timespec(timespec_to_ns(&now) - timespec_to_ns(&sys));

	wc.sec = boot.tv_sec;
	wc.nsec = boot.tv_nsec;
	wc.version = version;

	kvm_write_guest(kvm, wall_clock, &wc, sizeof(wc));

	version++;
	kvm_write_guest(kvm, wall_clock, &version, sizeof(version));
}