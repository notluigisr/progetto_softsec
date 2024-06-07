static void rtl8139_set_next_tctr_time(RTL8139State *s)
{
    const uint64_t ns_per_period = (uint64_t)PCI_PERIOD << 32;

    DPRINTF("STR");

    
    while (s->TCTR_base + ns_per_period <= qemu_clock_get_ns(QEMU_CLOCK_VIRTUAL)) {
        s->TCTR_base += ns_per_period;
    }

    if (!s->TimerInt) {
        timer_del(s->timer);
    } else {
        uint64_t delta = (uint64_t)s->TimerInt * PCI_PERIOD;
        if (s->TCTR_base + delta <= qemu_clock_get_ns(QEMU_CLOCK_VIRTUAL)) {
            delta += ns_per_period;
        }
        timer_mod(s->timer, s->TCTR_base + delta);
    }
}