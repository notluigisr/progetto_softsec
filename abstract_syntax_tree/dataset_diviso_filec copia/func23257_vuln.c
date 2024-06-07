static void *create_core_server_config(apr_pool_t *a, server_rec *s)
{
    core_server_config *conf;
    int is_virtual = s->is_virtual;

    conf = (core_server_config *)apr_pcalloc(a, sizeof(core_server_config));

    

    if (!is_virtual) {
        conf->ap_document_root = DOCUMENT_LOCATION;
        conf->access_name = DEFAULT_ACCESS_FNAME;

        
        conf->accf_map = apr_table_make(a, 5);
#if APR_HAS_SO_ACCEPTFILTER
        apr_table_setn(conf->accf_map, "STR", ACCEPT_FILTER_NAME);
        apr_table_setn(conf->accf_map, "STR");
#elif defined(WIN32)
        
        apr_table_setn(conf->accf_map, "STR");
        apr_table_setn(conf->accf_map, "STR");
#else
        apr_table_setn(conf->accf_map, "STR");
        apr_table_setn(conf->accf_map, "STR");
#endif

        conf->flush_max_threshold = AP_FLUSH_MAX_THRESHOLD;
        conf->flush_max_pipelined = AP_FLUSH_MAX_PIPELINED;
    }
    else {
        conf->flush_max_pipelined = -1;
    }

    

    conf->sec_dir = apr_array_make(a, 40, sizeof(ap_conf_vector_t *));
    conf->sec_url = apr_array_make(a, 40, sizeof(ap_conf_vector_t *));

    

    conf->trace_enable = AP_TRACE_UNSET;

    conf->protocols = apr_array_make(a, 5, sizeof(const char *));
    conf->protocols_honor_order = -1;
    conf->merge_slashes = AP_CORE_CONFIG_UNSET; 
    
    return (void *)conf;
}