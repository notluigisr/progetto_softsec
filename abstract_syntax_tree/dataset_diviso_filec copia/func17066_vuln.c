evtchn_port_t evtchn_from_irq(unsigned irq)
{
	if (WARN(irq >= nr_irqs, "STR", irq))
		return 0;

	return info_for_irq(irq)->evtchn;
}