handle_tftp_ctl(struct conntrack *ct,
                const struct conn_lookup_ctx *ctx OVS_UNUSED,
                struct dp_packet *pkt, struct conn *conn_for_expectation,
                long long now OVS_UNUSED, enum ftp_ctl_pkt ftp_ctl OVS_UNUSED,
                bool nat OVS_UNUSED)
{
    expectation_create(ct, conn_for_expectation->key.src.port,
                       conn_for_expectation,
                       !!(pkt->md.ct_state & CS_REPLY_DIR), false, false);
}