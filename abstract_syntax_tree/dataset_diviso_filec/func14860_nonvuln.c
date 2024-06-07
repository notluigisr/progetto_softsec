dp_packet_hwol_set_csum_tcp(struct dp_packet *b)
{
    b->mbuf.ol_flags |= PKT_TX_TCP_CKSUM;
}