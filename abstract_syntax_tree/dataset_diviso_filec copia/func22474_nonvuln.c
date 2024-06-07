dp_packet_l4_checksum_valid(const struct dp_packet *p)
{
    return (p->mbuf.ol_flags & PKT_RX_L4_CKSUM_MASK) ==
            PKT_RX_L4_CKSUM_GOOD;
}