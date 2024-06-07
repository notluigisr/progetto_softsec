void h2_mplx_release_and_join(h2_mplx *m, apr_thread_cond_t *wait)
{
    apr_status_t status;
    int i, wait_secs = 60;

    
    m->aborted = 1;
    h2_workers_unregister(m->workers, m);
    
    H2_MPLX_ENTER_ALWAYS(m);

    
    while (!h2_ihash_iter(m->streams, stream_cancel_iter, m)) {
        
    }
    
    
    h2_ngn_shed_abort(m->ngn_shed);
    ap_assert(h2_ihash_empty(m->streams));
    ap_assert(h2_iq_empty(m->q));
    
        
    m->join_wait = wait;
    for (i = 0; h2_ihash_count(m->shold) > 0; ++i) {        
        status = apr_thread_cond_timedwait(wait, m->lock, apr_time_from_sec(wait_secs));
        
        if (APR_STATUS_IS_TIMEUP(status)) {
            
            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, m->c, APLOGNO(03198)
                          "STR", 
                          m->id, i*wait_secs, (int)h2_ihash_count(m->shold));
            h2_ihash_iter(m->shold, report_stream_iter, m);
        }
    }
    ap_assert(m->tasks_active == 0);
    m->join_wait = NULL;
    
    
    h2_ngn_shed_destroy(m->ngn_shed);
    m->ngn_shed = NULL;
    
    
    if (!h2_ihash_empty(m->shold)) {
        ap_log_cerror(APLOG_MARK, APLOG_WARNING, 0, m->c, APLOGNO(03516)
                      "STR", 
                      m->id, (int)h2_ihash_count(m->shold));
        h2_ihash_iter(m->shold, unexpected_stream_iter, m);
    }
    
    H2_MPLX_LEAVE(m);

    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, m->c,
                  "STR", m->id);
}