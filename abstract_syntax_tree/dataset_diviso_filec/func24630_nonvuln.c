conntrack_dump_next(struct conntrack_dump *dump, struct ct_dpif_entry *entry)
{
    struct conntrack *ct = dump->ct;
    long long now = time_msec();

    while (dump->bucket < CONNTRACK_BUCKETS) {
        struct hmap_node *node;

        ct_lock_lock(&ct->buckets[dump->bucket].lock);
        for (;;) {
            struct conn *conn;

            node = hmap_at_position(&ct->buckets[dump->bucket].connections,
                                    &dump->bucket_pos);
            if (!node) {
                break;
            }
            INIT_CONTAINER(conn, node, node);
            if ((!dump->filter_zone || conn->key.zone == dump->zone) &&
                 (conn->conn_type != CT_CONN_TYPE_UN_NAT)) {
                conn_to_ct_dpif_entry(conn, entry, now, dump->bucket);
                break;
            }
            
        }
        ct_lock_unlock(&ct->buckets[dump->bucket].lock);

        if (!node) {
            memset(&dump->bucket_pos, 0, sizeof dump->bucket_pos);
            dump->bucket++;
        } else {
            return 0;
        }
    }
    return EOF;
}