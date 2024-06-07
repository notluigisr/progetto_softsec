static void ev_stream_closed(h2_session *session, h2_stream *stream)
{
    apr_bucket *b;
    
    if (H2_STREAM_CLIENT_INITIATED(stream->id)
        && (stream->id > session->local.completed_max)) {
        session->local.completed_max = stream->id;
    }
    switch (session->state) {
        case H2_SESSION_ST_IDLE:
            if (session->open_streams == 0) {
                
                session->idle_until = (session->s->keep_alive_timeout
                                       + apr_time_now());
            }
            break;
        default:
            break;
    }
    
    
    b = h2_bucket_eos_create(session->c->bucket_alloc, stream);
    APR_BRIGADE_INSERT_TAIL(session->bbtmp, b);
    h2_conn_io_pass(&session->io, session->bbtmp);
    apr_brigade_cleanup(session->bbtmp);
}