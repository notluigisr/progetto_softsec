static void ndpi_reconcile_protocols(struct ndpi_detection_module_struct *ndpi_str,
				     struct ndpi_flow_struct *flow,
				     ndpi_protocol *ret) {
  
  
  if(flow) {
    
    if((flow->detected_protocol_stack[1] != NDPI_PROTOCOL_UNKNOWN)
       && (flow->detected_protocol_stack[0]  != flow->detected_protocol_stack[1] ))
      NDPI_CLR_BIT(flow->risk, NDPI_SUSPICIOUS_DGA_DOMAIN);
  }  

  switch(ret->app_protocol) {
  case NDPI_PROTOCOL_MSTEAMS:
    if(flow->packet.iph && flow->packet.tcp) {
      

      if(ndpi_str->msteams_cache == NULL)
	ndpi_str->msteams_cache = ndpi_lru_cache_init(1024);

      if(ndpi_str->msteams_cache)
	ndpi_lru_add_to_cache(ndpi_str->msteams_cache,
			      flow->packet.iph->saddr,
			      (flow->packet.current_time_ms / 1000) & 0xFFFF );
    }
    break;

  case NDPI_PROTOCOL_SKYPE:
  case NDPI_PROTOCOL_SKYPE_CALL:
    if(flow->packet.iph
       && flow->packet.udp
       && ndpi_str->msteams_cache) {
      u_int16_t when;

      if(ndpi_lru_find_cache(ndpi_str->msteams_cache, flow->packet.iph->saddr,
			     &when, 0 )) {
	u_int16_t tdiff = ((flow->packet.current_time_ms /1000) & 0xFFFF) - when;

	if(tdiff < 60 ) {
	  
	  ret->app_protocol = NDPI_PROTOCOL_MSTEAMS;

	  
	  ndpi_lru_add_to_cache(ndpi_str->msteams_cache,
				flow->packet.iph->saddr,
				(flow->packet.current_time_ms / 1000) & 0xFFFF );
	}
      }
    }
    break;
  } 
}