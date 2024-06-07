static void ev_proto_error(h2_proxy_session *session, int arg, const char *msg)
{
    switch (session->state) {
        case H2_PROXYS_ST_DONE:
        case H2_PROXYS_ST_LOCAL_SHUTDOWN:
            
            transit(session, "STR", H2_PROXYS_ST_DONE);
            break;
        
        default:
            ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, session->c,
                          "STR", session->id);
            session_shutdown(session, arg, msg);
            break;
    }
}