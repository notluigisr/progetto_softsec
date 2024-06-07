am_cache_entry_t *am_lock_and_validate(request_rec *r,
                                       am_cache_key_t type,
                                       const char *key)
{
    am_cache_entry_t *session = am_cache_lock(r->server, type, key);
    if (session == NULL) {
        return NULL;
    }

    const char *cookie_token_session = am_cache_entry_get_string(
        session, &session->cookie_token);
    const char *cookie_token_target = am_cookie_token(r);
    if (strcmp(cookie_token_session, cookie_token_target)) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "STR"
                      "STR"
                      "STR",
                      cookie_token_session,
                      cookie_token_target);
        am_cache_unlock(r->server, session);
        return NULL;
    }

    return session;
}