dns_init()
{
  ip_addr_t dnsserver;

  LWIP_ASSERT("STR",
    sizeof(struct dns_query) == SIZEOF_DNS_QUERY);
  LWIP_ASSERT("STR",
    sizeof(struct dns_answer) <= SIZEOF_DNS_ANSWER_ASSERT);

  dns_payload = (u8_t *)LWIP_MEM_ALIGN(dns_payload_buffer);

  
  DNS_SERVER_ADDRESS(&dnsserver);

  LWIP_DEBUGF(DNS_DEBUG, ("STR"));

  
  if (dns_pcb == NULL) {
    dns_pcb = udp_new();

    if (dns_pcb != NULL) {
      
      LWIP_ASSERT("STR",
        DNS_STATE_UNUSED == 0);

      
      udp_bind(dns_pcb, IP_ADDR_ANY, 0);
      udp_recv(dns_pcb, dns_recv, NULL);

      
      dns_setserver(0, &dnsserver);
    }
  }
#if DNS_LOCAL_HOSTLIST
  dns_init_local();
#endif
}