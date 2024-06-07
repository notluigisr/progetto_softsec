dp_packet_set_l4(struct dp_packet *b, void *l4)
{
    b->l4_ofs = l4 ? (char *) l4 - (char *) dp_packet_data(b) : UINT16_MAX;
}