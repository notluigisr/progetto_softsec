flow_compose_l4_csum(struct dp_packet *p, const struct flow *flow,
                     uint32_t pseudo_hdr_csum)
{
    size_t l4_len = (char *) dp_packet_tail(p) - (char *) dp_packet_l4(p);

    if (!(flow->nw_frag & FLOW_NW_FRAG_ANY)
        || !(flow->nw_frag & FLOW_NW_FRAG_LATER)) {
        if (flow->nw_proto == IPPROTO_TCP) {
            struct tcp_header *tcp = dp_packet_l4(p);

            tcp->tcp_csum = 0;
            tcp->tcp_csum = csum_finish(csum_continue(pseudo_hdr_csum,
                                                      tcp, l4_len));
        } else if (flow->nw_proto == IPPROTO_UDP) {
            struct udp_header *udp = dp_packet_l4(p);

            udp->udp_csum = 0;
            udp->udp_csum = csum_finish(csum_continue(pseudo_hdr_csum,
                                                      udp, l4_len));
        } else if (flow->nw_proto == IPPROTO_ICMP) {
            struct icmp_header *icmp = dp_packet_l4(p);

            icmp->icmp_csum = 0;
            icmp->icmp_csum = csum(icmp, l4_len);
        } else if (flow->nw_proto == IPPROTO_IGMP) {
            struct igmp_header *igmp = dp_packet_l4(p);

            igmp->igmp_csum = 0;
            igmp->igmp_csum = csum(igmp, l4_len);
        } else if (flow->nw_proto == IPPROTO_ICMPV6) {
            struct icmp6_hdr *icmp = dp_packet_l4(p);

            icmp->icmp6_cksum = 0;
            icmp->icmp6_cksum = (OVS_FORCE uint16_t)
                csum_finish(csum_continue(pseudo_hdr_csum, icmp, l4_len));
        }
    }
}