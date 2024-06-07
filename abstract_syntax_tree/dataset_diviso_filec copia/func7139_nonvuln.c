parse_dl_type(const struct eth_header *data_, size_t size)
{
    const void *data = data_;
    union flow_vlan_hdr vlans[FLOW_MAX_VLAN_HEADERS];

    parse_vlan(&data, &size, vlans);

    return parse_ethertype(&data, &size);
}