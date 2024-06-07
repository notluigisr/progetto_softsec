static void xen_hvm_crash_shutdown(struct pt_regs *regs)
{
	native_machine_crash_shutdown(regs);
	xen_reboot(SHUTDOWN_soft_reset);
}