static void ndpi_int_tls_add_connection(struct ndpi_detection_module_struct *ndpi_struct,
					struct ndpi_flow_struct *flow, u_int32_t protocol) {
#if DEBUG_TLS
  printf("STR", __FUNCTION__);
#endif

  if((flow->packet.udp != NULL) && (protocol == NDPI_PROTOCOL_TLS))
    protocol = NDPI_PROTOCOL_DTLS;

  if((flow->detected_protocol_stack[0] == protocol)
     || (flow->detected_protocol_stack[1] == protocol)) {
    if(!flow->check_extra_packets)
      tlsInitExtraPacketProcessing(ndpi_struct, flow);
    return;
  }

  if(protocol != NDPI_PROTOCOL_TLS)
    ;
  else
    protocol = ndpi_tls_refine_master_protocol(ndpi_struct, flow, protocol);

  ndpi_set_detected_protocol(ndpi_struct, flow, protocol, protocol);

  tlsInitExtraPacketProcessing(ndpi_struct, flow);
}