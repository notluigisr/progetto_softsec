static void transit(h2_session *session, const char *action, h2_session_state nstate)
{
    apr_time_t timeout;
    int ostate, loglvl;
    const char *s;
    
    if (session->state != nstate) {
        ostate = session->state;
        session->state = nstate;
        
        loglvl = APLOG_DEBUG;
        if ((ostate == H2_SESSION_ST_BUSY && nstate == H2_SESSION_ST_WAIT)
            || (ostate == H2_SESSION_ST_WAIT && nstate == H2_SESSION_ST_BUSY)){
            loglvl = APLOG_TRACE1;
        }
        ap_log_cerror(APLOG_MARK, loglvl, 0, session->c, 
                      H2_SSSN_LOG(APLOGNO(03078), session, 
                      "STR"), 
                      h2_session_state_str(ostate), action, 
                      h2_session_state_str(nstate));
        
        switch (session->state) {
            case H2_SESSION_ST_IDLE:
                if (!session->remote.emitted_count) {
                    
                    session->idle_sync_until = apr_time_now() + apr_time_from_sec(1);
                    s = "STR";
                    timeout = H2MAX(session->s->timeout, session->s->keep_alive_timeout);
                    update_child_status(session, SERVER_BUSY_READ, "STR");
                    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, session->c, 
                                  H2_SSSN_LOG("STR"), 
                                  (int)apr_time_sec(H2MAX(session->s->timeout, session->s->keep_alive_timeout)));
                }
                else if (session->open_streams) {
                    s = "STR";
                    timeout = session->s->keep_alive_timeout;
                    update_child_status(session, SERVER_BUSY_KEEPALIVE, "STR");
                }
                else {
                    
                    s = "STR";
                    timeout = session->s->keep_alive_timeout;
                    update_child_status(session, SERVER_BUSY_KEEPALIVE, "STR");
                }
                session->idle_until = apr_time_now() + timeout; 
                ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, session->c, 
                              H2_SSSN_LOG("STR"), 
                              s, (int)apr_time_sec(timeout));
                break;
            case H2_SESSION_ST_DONE:
                update_child_status(session, SERVER_CLOSING, "STR");
                break;
            default:
                
                break;
        }
    }
}