conntrack_get_tcp_seq_chk(struct conntrack *ct)
{
    bool enabled;
    atomic_read_relaxed(&ct->tcp_seq_chk, &enabled);
    return enabled;
}