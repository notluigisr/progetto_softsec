uipbuf_get_next_header(uint8_t *buffer, uint16_t size, uint8_t *protocol, bool start)
{
  int curr_hdr_len = 0;
  int next_hdr_len = 0;
  uint8_t *next_header = NULL;
  struct uip_ip_hdr *ipbuf = NULL;
  struct uip_ext_hdr *curr_ext = NULL;
  struct uip_ext_hdr *next_ext = NULL;

  if(start) {
    
    ipbuf = (struct uip_ip_hdr *)buffer;
    *protocol = ipbuf->proto;
    curr_hdr_len = UIP_IPH_LEN;
  } else {
    
    curr_ext = (struct uip_ext_hdr *)buffer;
    *protocol = curr_ext->next;
    
    curr_hdr_len = (curr_ext->len << 3) + 8;
  }

  
  if(curr_hdr_len > size) {
    return NULL;
  }
  next_header = buffer + curr_hdr_len;

  
  if(uip_is_proto_ext_hdr(*protocol)) {
    next_ext = (struct uip_ext_hdr *)next_header;
    next_hdr_len = (next_ext->len << 3) + 8;
  } else {
    if(*protocol == UIP_PROTO_TCP) {
      next_hdr_len = UIP_TCPH_LEN;
    } else if(*protocol == UIP_PROTO_UDP) {
      next_hdr_len = UIP_UDPH_LEN;
    } else if(*protocol == UIP_PROTO_ICMP6) {
      next_hdr_len = UIP_ICMPH_LEN;
    }
  }

  
  if(next_hdr_len == 0 || curr_hdr_len + next_hdr_len > size) {
    return NULL;
  }

  return next_header;
}