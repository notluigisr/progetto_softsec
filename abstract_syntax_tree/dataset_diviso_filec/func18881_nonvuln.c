njs_object_property_init(njs_lvlhsh_query_t *lhq, const njs_value_t *key,
    uint32_t hash)
{
    lhq->proto = &njs_object_hash_proto;

    njs_object_property_key_set(lhq, key, hash);
}