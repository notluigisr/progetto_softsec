static inline void xen_evtchn_handle_events(unsigned cpu)
{
	return evtchn_ops->handle_events(cpu);
}