pblock_analytics_init(Slapi_PBlock *pb)
{
    if (pblock_analytics_lock == NULL) {
        pblock_analytics_lock = PR_NewLock();
    }
    
    if (pb->analytics == NULL) {
        pb->analytics = PL_NewHashTable(NUMBER_SLAPI_ATTRS, hash_int_func, hash_key_compare, hash_value_compare, NULL, NULL);
    }
    pb->analytics_init = ANALYTICS_MAGIC;
}