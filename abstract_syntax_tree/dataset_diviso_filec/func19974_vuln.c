dns_tmr(void)
{
  if (dns_pcb != NULL) {
    LWIP_DEBUGF(DNS_DEBUG, ("STR"));
    dns_check_entries();
  }
}