ct_dpif_inet_addr_to_ct_endpoint(const union ct_dpif_inet_addr *a,
                                 union ct_addr *b, ovs_be16 dl_type)
{
    if (dl_type == htons(ETH_TYPE_IP)) {
        b->ipv4 = a->ip;
    } else if (dl_type == htons(ETH_TYPE_IPV6)){
        b->ipv6 = a->in6;
    }
}