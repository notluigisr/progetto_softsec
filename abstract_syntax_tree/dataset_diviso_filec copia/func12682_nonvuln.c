extract_l4_icmp6(struct conn_key *key, const void *data, size_t size,
                 bool *related)
{
    const struct icmp6_header *icmp6 = data;

    
    if (size < sizeof *icmp6 + 4) {
        return false;
    }

    switch (icmp6->icmp6_type) {
    case ICMP6_ECHO_REQUEST:
    case ICMP6_ECHO_REPLY:
        if (icmp6->icmp6_code != 0) {
            return false;
        }
        
        key->src.icmp_id = key->dst.icmp_id = *(ovs_be16 *) (icmp6 + 1);
        key->src.icmp_type = icmp6->icmp6_type;
        key->dst.icmp_type = reverse_icmp6_type(icmp6->icmp6_type);
        break;
    case ICMP6_DST_UNREACH:
    case ICMP6_PACKET_TOO_BIG:
    case ICMP6_TIME_EXCEEDED:
    case ICMP6_PARAM_PROB: {
        
        struct conn_key inner_key;
        const char *l3 = (const char *) icmp6 + 8;
        const char *tail = (const char *) data + size;
        const char *l4 = NULL;
        bool ok;

        if (!related) {
            return false;
        }

        memset(&inner_key, 0, sizeof inner_key);
        inner_key.dl_type = htons(ETH_TYPE_IPV6);
        ok = extract_l3_ipv6(&inner_key, l3, tail - l3, &l4);
        if (!ok) {
            return false;
        }

        
        if (!ipv6_addr_equals(&inner_key.src.addr.ipv6_aligned,
                              &key->dst.addr.ipv6_aligned)) {
            return false;
        }

        key->src = inner_key.src;
        key->dst = inner_key.dst;
        key->nw_proto = inner_key.nw_proto;

        ok = extract_l4(key, l4, tail - l4, NULL, l3, false, NULL);
        if (ok) {
            conn_key_reverse(key);
            *related = true;
        }
        return ok;
    }
    default:
        return false;
    }

    return true;
}