expectation_clean(struct conntrack *ct, const struct conn_key *master_key)
{
    ovs_rwlock_wrlock(&ct->resources_lock);

    struct alg_exp_node *node, *next;
    HINDEX_FOR_EACH_WITH_HASH_SAFE (node, next, node_ref,
                                    conn_key_hash(master_key, ct->hash_basis),
                                    &ct->alg_expectation_refs) {
        if (!conn_key_cmp(&node->master_key, master_key)) {
            expectation_remove(&ct->alg_expectations, &node->key,
                               ct->hash_basis);
            hindex_remove(&ct->alg_expectation_refs, &node->node_ref);
            free(node);
        }
    }

    ovs_rwlock_unlock(&ct->resources_lock);
}