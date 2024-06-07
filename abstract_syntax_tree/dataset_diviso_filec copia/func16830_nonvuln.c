slapi_config_register_callback_plugin(int operation,
                                      int flags,
                                      const char *base,
                                      int scope,
                                      const char *filter,
                                      dseCallbackFn fn,
                                      void *fn_arg,
                                      Slapi_PBlock *pb)
{
    int rc = 0;
    Slapi_Backend *be = slapi_be_select_by_instance_name(DSE_BACKEND);
    if (be != NULL) {
        struct dse *pdse = (struct dse *)be->be_database->plg_private;
        if (pdse != NULL) {
            Slapi_DN dn;
            slapi_sdn_init_dn_byref(&dn, base);
            if (pb != NULL) {
                
                struct slapdplugin *pb_plugin = NULL;
                slapi_pblock_get(pb, SLAPI_PLUGIN, &pb_plugin);
                rc = (NULL != dse_register_callback(pdse, operation, flags, &dn, scope, filter, fn,
                                                    (void *)pb_plugin, pb_plugin));
            } else {
                rc = (NULL != dse_register_callback(pdse, operation, flags, &dn, scope, filter, fn,
                                                    fn_arg, NULL));
            }

            slapi_sdn_done(&dn);
        }
    }
    return rc;
}