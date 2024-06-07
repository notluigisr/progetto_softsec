miniflow_hash_5tuple(const struct miniflow *flow, uint32_t basis)
{
    BUILD_ASSERT_DECL(FLOW_WC_SEQ == 36);
    uint32_t hash = basis;

    if (flow) {
        ovs_be16 dl_type = MINIFLOW_GET_BE16(flow, dl_type);
        uint8_t nw_proto;

        if (dl_type == htons(ETH_TYPE_IPV6)) {
            struct flowmap map = FLOWMAP_EMPTY_INITIALIZER;
            uint64_t value;

            FLOWMAP_SET(&map, ipv6_src);
            FLOWMAP_SET(&map, ipv6_dst);

            MINIFLOW_FOR_EACH_IN_FLOWMAP(value, flow, map) {
                hash = hash_add64(hash, value);
            }
        } else if (dl_type == htons(ETH_TYPE_IP)
                   || dl_type == htons(ETH_TYPE_ARP)) {
            hash = hash_add(hash, MINIFLOW_GET_U32(flow, nw_src));
            hash = hash_add(hash, MINIFLOW_GET_U32(flow, nw_dst));
        } else {
            goto out;
        }

        nw_proto = MINIFLOW_GET_U8(flow, nw_proto);
        hash = hash_add(hash, nw_proto);
        if (nw_proto != IPPROTO_TCP && nw_proto != IPPROTO_UDP
            && nw_proto != IPPROTO_SCTP && nw_proto != IPPROTO_ICMP
            && nw_proto != IPPROTO_ICMPV6) {
            goto out;
        }

        
        hash = hash_add(hash, MINIFLOW_GET_U32(flow, tp_src));
    }
out:
    return hash_finish(hash, 42);
}