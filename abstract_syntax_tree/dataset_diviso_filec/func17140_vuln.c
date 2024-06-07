am_cache_entry_t *am_new_request_session(request_rec *r)
{
    const char *session_id;

    
    session_id = am_generate_id(r);
    if(session_id == NULL) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "STR");
        return NULL;
    }


    
    am_cookie_set(r, session_id);

    return am_cache_new(r->server, session_id);
}