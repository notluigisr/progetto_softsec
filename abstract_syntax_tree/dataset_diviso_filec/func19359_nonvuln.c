dp_packet_set_rss_hash(struct dp_packet *p, uint32_t hash)
{
    p->rss_hash = hash;
    p->ol_flags |= DP_PACKET_OL_RSS_HASH_MASK;
}