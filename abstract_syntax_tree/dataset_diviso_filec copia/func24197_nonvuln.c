dse_search_set_delete(dse_search_set *ss)
{
    if (ss) {
        dl_cleanup(&ss->dl, dse_free_entry);
        slapi_ch_free((void **)&ss);
    }
}