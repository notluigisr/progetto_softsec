void ipmi_irq_start_cleanup(struct si_sm_io *io)
{
	if (io->si_type == SI_BT)
		
		io->outputb(io, IPMI_BT_INTMASK_REG, 0);
}