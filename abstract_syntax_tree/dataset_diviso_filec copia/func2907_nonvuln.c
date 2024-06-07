dp_packet_ip_checksum_bad(const struct dp_packet *p)
{
    return (p->mbuf.ol_flags & PKT_RX_IP_CKSUM_MASK) ==
            PKT_RX_IP_CKSUM_BAD;
}