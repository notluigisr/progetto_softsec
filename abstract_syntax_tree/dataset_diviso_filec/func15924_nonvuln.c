megasas_check_reset_xscale(struct megasas_instance *instance,
		struct megasas_register_set __iomem *regs)
{
	if ((atomic_read(&instance->adprecovery) != MEGASAS_HBA_OPERATIONAL) &&
	    (le32_to_cpu(*instance->consumer) ==
		MEGASAS_ADPRESET_INPROG_SIGN))
		return 1;
	return 0;
}