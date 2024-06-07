static u64 xen_read_msr(unsigned int msr)
{
	
	int err;

	return xen_read_msr_safe(msr, &err);
}