int bind_evtchn_to_irq_lateeoi(evtchn_port_t evtchn)
{
	return bind_evtchn_to_irq_chip(evtchn, &xen_lateeoi_chip);
}