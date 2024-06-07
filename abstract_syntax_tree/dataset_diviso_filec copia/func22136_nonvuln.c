parse_dl_type(const struct eth_header *data_, size_t size)
{
    const void *data = data_;

    parse_vlan(&data, &size);

    return parse_ethertype(&data, &size);
}