conn_key_hash(const struct conn_key *key, uint32_t basis)
{
    uint32_t hsrc, hdst, hash;
    hsrc = hdst = basis;
    hsrc = ct_endpoint_hash_add(hsrc, &key->src);
    hdst = ct_endpoint_hash_add(hdst, &key->dst);

    
    hash = hsrc ^ hdst;

    
    return hash_words((uint32_t *) (&key->dst + 1),
                      (uint32_t *) (key + 1) - (uint32_t *) (&key->dst + 1),
                      hash);
}