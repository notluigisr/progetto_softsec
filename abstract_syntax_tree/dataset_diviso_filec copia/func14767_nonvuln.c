dp_packet_hwol_l4_is_tcp(const struct dp_packet *b)
{
    return (b->mbuf.ol_flags & PKT_TX_L4_MASK) == PKT_TX_TCP_CKSUM;
}