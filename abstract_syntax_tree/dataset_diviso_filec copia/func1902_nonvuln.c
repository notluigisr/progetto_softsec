extract_l3_ipv4(struct conn_key *key, const void *data, size_t size,
                const char **new_data, bool validate_checksum)
{
    const struct ip_header *ip = data;
    size_t ip_len;

    if (new_data) {
        if (OVS_UNLIKELY(size < IP_HEADER_LEN)) {
            return false;
        }
    }

    ip_len = IP_IHL(ip->ip_ihl_ver) * 4;

    if (new_data) {
        if (OVS_UNLIKELY(ip_len < IP_HEADER_LEN)) {
            return false;
        }
        if (OVS_UNLIKELY(size < ip_len)) {
            return false;
        }

        *new_data = (char *) data + ip_len;
    }

    if (IP_IS_FRAGMENT(ip->ip_frag_off)) {
        return false;
    }

    if (validate_checksum && csum(data, ip_len) != 0) {
        return false;
    }

    key->src.addr.ipv4 = ip->ip_src;
    key->dst.addr.ipv4 = ip->ip_dst;
    key->nw_proto = ip->ip_proto;

    return true;
}