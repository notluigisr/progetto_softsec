new_conn(struct conntrack_bucket *ctb, struct dp_packet *pkt,
         struct conn_key *key, long long now)
{
    return l4_protos[key->nw_proto]->new_conn(ctb, pkt, now);
}