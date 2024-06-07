packet_batch_init_packet(struct dp_packet_batch *b, struct dp_packet *p)
{
    b->count = 1;
    b->trunc = false;
    b->packets[0] = p;
}