dse_get_entry_copy(struct dse *pdse, const Slapi_DN *dn, int use_lock)
{
    Slapi_Entry *e = NULL;
    struct dse_node *n;

    if (use_lock == DSE_USE_LOCK && pdse->dse_rwlock) {
        slapi_rwlock_rdlock(pdse->dse_rwlock);
    }

    n = dse_find_node(pdse, dn);
    if (n != NULL) {
        e = slapi_entry_dup(n->entry);
    }

    if (use_lock == DSE_USE_LOCK && pdse->dse_rwlock) {
        slapi_rwlock_unlock(pdse->dse_rwlock);
    }

    return e;
}