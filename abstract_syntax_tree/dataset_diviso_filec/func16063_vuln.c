am_cache_entry_t *am_get_request_session(request_rec *r)
{
    const char *session_id;

    
    session_id = am_cookie_get(r);
    if(session_id == NULL) {
        
        return NULL;
    }

    return am_cache_lock(r->server, AM_CACHE_SESSION, session_id);
}