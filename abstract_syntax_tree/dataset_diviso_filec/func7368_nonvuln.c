void xen_reboot(int reason)
{
	struct sched_shutdown r = { .reason = reason };
	int rc;

	rc = HYPERVISOR_sched_op(SCHEDOP_shutdown, &r);
	BUG_ON(rc);
}