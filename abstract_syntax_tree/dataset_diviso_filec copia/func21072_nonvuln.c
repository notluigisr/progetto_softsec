void am_cache_init(am_mod_cfg_rec *mod_cfg)
{
    void *table;
    apr_size_t i;
    
    table = apr_shm_baseaddr_get(mod_cfg->cache);
    for (i = 0; i < mod_cfg->init_cache_size; i++) {
        am_cache_entry_t *e = am_cache_entry_ptr(mod_cfg, table, i);
        e->key[0] = '\0';
        e->access = 0;
    }
}