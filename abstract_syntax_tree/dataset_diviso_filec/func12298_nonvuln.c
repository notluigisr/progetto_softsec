ldbm_config_destroy(struct ldbminfo *li)
{
    if (li->li_attrs_to_exclude_from_export != NULL) {
        charray_free(li->li_attrs_to_exclude_from_export);
    }
    slapi_ch_free((void **)&(li->li_new_directory));
    slapi_ch_free((void **)&(li->li_directory));
    slapi_ch_free((void **)&(li->li_backend_implement));
    
    PR_DestroyLock(li->li_shutdown_mutex);
    PR_DestroyLock(li->li_config_mutex);

    
    slapi_ch_free((void **)&li);
}