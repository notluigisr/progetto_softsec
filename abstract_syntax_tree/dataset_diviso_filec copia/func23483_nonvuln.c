static int bind_interdomain_evtchn_to_irq_chip(unsigned int remote_domain,
					       evtchn_port_t remote_port,
					       struct irq_chip *chip)
{
	struct evtchn_bind_interdomain bind_interdomain;
	int err;

	bind_interdomain.remote_dom  = remote_domain;
	bind_interdomain.remote_port = remote_port;

	err = HYPERVISOR_event_channel_op(EVTCHNOP_bind_interdomain,
					  &bind_interdomain);

	return err ? : bind_evtchn_to_irq_chip(bind_interdomain.local_port,
					       chip);
}