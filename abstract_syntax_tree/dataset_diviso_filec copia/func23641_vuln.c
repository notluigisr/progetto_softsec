static void on_stream_state_enter(void *ctx, h2_stream *stream)
{
    h2_session *session = ctx;
    
    ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, session->c,
                  H2_STRM_MSG(stream, "STR"));
    switch (stream->state) {
        case H2_SS_IDLE: 
            ++session->open_streams;
            if (H2_STREAM_CLIENT_INITIATED(stream->id)) {
                ++session->remote.emitted_count;
                if (stream->id > session->remote.emitted_max) {
                    session->remote.emitted_max = stream->id;
                    session->local.accepted_max = stream->id;
                }
            }
            else {
                if (stream->id > session->local.emitted_max) {
                    ++session->local.emitted_count;
                    session->remote.emitted_max = stream->id;
                }
            }
            break;
        case H2_SS_OPEN: 
        case H2_SS_RSVD_L: 
            ev_stream_open(session, stream);
            break;
        case H2_SS_CLOSED_L: 
            break;
        case H2_SS_CLOSED_R: 
            break;
        case H2_SS_CLOSED: 
            --session->open_streams;
            ev_stream_closed(session, stream);
            break;
        case H2_SS_CLEANUP:
            h2_mplx_stream_cleanup(session->mplx, stream);
            break;
        default:
            break;
    }
}