flow_wildcards_has_extra(const struct flow_wildcards *a,
                         const struct flow_wildcards *b)
{
    const uint64_t *a_u64 = (const uint64_t *) &a->masks;
    const uint64_t *b_u64 = (const uint64_t *) &b->masks;
    size_t i;

    for (i = 0; i < FLOW_U64S; i++) {
        if ((a_u64[i] & b_u64[i]) != b_u64[i]) {
            return true;
        }
    }
    return false;
}