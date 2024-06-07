bool mce_is_memory_error(struct mce *m)
{
	if (m->cpuvendor == X86_VENDOR_AMD) {
		return amd_mce_is_memory_error(m);

	} else if (m->cpuvendor == X86_VENDOR_INTEL) {
		
		return (m->status & 0xef80) == BIT(7) ||
		       (m->status & 0xef00) == BIT(8) ||
		       (m->status & 0xeffc) == 0xc;
	}

	return false;
}