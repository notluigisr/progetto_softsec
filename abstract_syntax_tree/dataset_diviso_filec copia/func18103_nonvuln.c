policies_copy_outbound_addresses_to_smartlist(smartlist_t *addr_list,
                                              const or_options_t *or_options)
{
  if (or_options) {
    policies_copy_addr_to_smartlist(addr_list,
                                    &or_options->OutboundBindAddressIPv4_);
    policies_copy_addr_to_smartlist(addr_list,
                                    &or_options->OutboundBindAddressIPv6_);
  }
}